#!/usr/bin/env pwsh

param(
    [Parameter(Mandatory = $true)]
    [string]$Compiler
)

$ErrorActionPreference = 'Stop'

function Invoke-Step([string]$name, [scriptblock]$body) {
    Write-Output "[CI] ==> $name"
    & $body
}

$buildDir = "build"

switch($Compiler) {
    "gcc" {
        $cc = "gcc"
        $cxx = "g++"
    }
    "clang" {
        $cc = "clang"
        $cxx = "clang++"
    }
    "clang-cl" {
        $cc = "clang-cl"
        $cxx = "clang-cl"
    }
    "msvc" {
        $cc = "cl"
        $cxx = "cl"
    }
    default {
        throw "Unknown compiler: $Compiler"
    }
}

Invoke-Step "Expand" {
    Set-Location "tests"
    if(Test-Path "expanded") {
        Remove-Item -Recurse -Force "expanded"
    }
    New-Item -ItemType Directory -Path "expanded" -Force
    Copy-Item -Path "expanded_cmakelists.txt" -Destination "expanded\CMakeLists.txt"
    [string[]]$cppFiles = @(
        Get-ChildItem -Recurse -File -Filter "*.cpp" -Path . | ForEach-Object {
            [System.IO.Path]::GetRelativePath((Resolve-Path ".").Path, $_.FullName)
        }
    )
    foreach($cppFile in $cppFiles) {
        if($cppFile.Contains("build")) { continue }
        $folder = Split-Path $cppFile -Parent
        $includeDir = [System.IO.Path]::Combine("..", "include", $folder)
        $outputPath = [System.IO.Path]::Combine("expanded", $cppFile)
        python ([System.IO.Path]::Combine("..", "expand.py")) $cppFile -I $includeDir -o $outputPath
        if ($LASTEXITCODE -ne 0) {
            throw "expand.py failed for $cppFile with exit code $LASTEXITCODE"
        }
    }
}
Invoke-Step "Configure" {
    Set-Location ".."
    cmake -S . -B $buildDir -G Ninja -D CMAKE_BUILD_TYPE=Release -D CMAKE_C_COMPILER=$cc -D CMAKE_CXX_COMPILER=$cxx
}
Invoke-Step "Build" {
    cmake --build $buildDir -j
}
Invoke-Step "Test" {
    ctest --test-dir $buildDir -V
}