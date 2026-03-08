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
function Test-LastExitCode([string]$message) {
    if($LASTEXITCODE -ne 0) {
        throw $message
    }
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
    $includeRoot = [System.IO.Path]::Combine("..", "include")
    [string[]]$includeDirs = @(
        (Resolve-Path $includeRoot).Path
        Get-ChildItem -Path $includeRoot -Directory -Recurse | ForEach-Object { $_.FullName }
    )
    [string[]]$cppFiles = @(
        Get-ChildItem -Recurse -File -Filter "*.cpp" -Path . | ForEach-Object {
            [System.IO.Path]::GetRelativePath((Resolve-Path ".").Path, $_.FullName)
        }
    )
    foreach($cppFile in $cppFiles) {
        if($cppFile.Contains("build")) { continue }
        $outputPath = [System.IO.Path]::Combine("expanded", $cppFile)
        $outputDir = Split-Path $outputPath -Parent
        if($outputDir -and -not (Test-Path $outputDir)) {
            New-Item -ItemType Directory -Path $outputDir -Force | Out-Null
        }

        $expandArgs = @($cppFile)
        foreach($includeDir in $includeDirs) {
            $expandArgs += @("-I", $includeDir)
        }
        $expandArgs += @("-o", $outputPath)

        python ([System.IO.Path]::Combine("..", "expand.py")) @expandArgs
        Test-LastExitCode "expand.py failed for $cppFile with exit code $LASTEXITCODE"
    }
}
Invoke-Step "Configure" {
    Set-Location ".."
    if(Test-Path $buildDir) {
        Remove-Item $buildDir -Recurse -Force
    }
    if($Compiler -eq "msvc") {
        $vswhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
        $vsPath = (& $vswhere -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath).Trim()
        $vcvarsall = Join-Path $vsPath "VC\Auxiliary\Build\vcvars64.bat"
        $envVars = cmd.exe /c "`"$vcvarsall`" > nul 2>&1 && set"
        foreach ($line in $envVars) {
            if ($line -match '^([^=]+)=(.+)$') {
                [System.Environment]::SetEnvironmentVariable($Matches[1], $Matches[2], "Process")
            }
        }
        cmake -S . -B $buildDir -G Ninja -D CMAKE_BUILD_TYPE=Release
    } else {
        cmake -S . -B $buildDir -G Ninja -D CMAKE_BUILD_TYPE=Release -D CMAKE_C_COMPILER=$cc -D CMAKE_CXX_COMPILER=$cxx
    }
    Test-LastExitCode "CMake configure failed, exit code is $LASTEXITCODE"
}
Invoke-Step "Build" {
    cmake --build $buildDir -j
    Test-LastExitCode "CMake build failed, exit code is $LASTEXITCODE"
}
Invoke-Step "Test" {
    ctest --test-dir $buildDir -V
    Test-LastExitCode "CTest failed, exit code is $LASTEXITCODE"
}