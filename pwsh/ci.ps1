#!/usr/bin/env pwsh

param(
    [Parameter(Mandatory = $true)]
    [string]$Compiler,
    [ValidateRange(0, 2)]
    [int]$OptimizeLevel = 0,
    [switch]$TestWithExpand,
    [switch]$TestWithoutExpand
)

Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

$prevLocation = Get-Location

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
$repoRoot = [System.IO.Path]::GetFullPath((Join-Path $PSScriptRoot ".."))
$useExpandedTests = "OFF"

if($TestWithExpand -and $TestWithoutExpand) {
    throw "TestWithExpand and TestWithoutExpand are mutually exclusive."
}
if(-not $TestWithExpand -and -not $TestWithoutExpand) {
    $TestWithExpand = $true
}
if($TestWithExpand) {
    $useExpandedTests = "ON"
}

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

if($TestWithExpand) {
    Invoke-Step "Expand" {
        Set-Location (Join-Path $repoRoot "tests")
        if(Test-Path "expanded") {
            Remove-Item -Recurse -Force "expanded"
        }
        New-Item -ItemType Directory -Path "expanded" -Force
        Copy-Item -Path "expanded_cmakelists.txt" -Destination "expanded\CMakeLists.txt"
        $includeRoot = Join-Path $repoRoot "include"
        [string[]]$includeDirs = @((Resolve-Path $includeRoot).Path)
        [string[]]$cppFiles = @(
            Get-ChildItem -Recurse -File -Filter "*.cpp" -Path . | ForEach-Object {
                [System.IO.Path]::GetRelativePath((Resolve-Path ".").Path, $_.FullName)
            }
        )
        $expandOperationScript = Join-Path $repoRoot "pwsh\expand.operation.ps1"
        . $expandOperationScript
        foreach($cppFile in $cppFiles) {
            if(($cppFile -split '[\\/]') -contains 'build') {
                continue
            }

            $outputPath = [System.IO.Path]::Combine("expanded", $cppFile)
            $outputDir = Split-Path $outputPath -Parent
            if($outputDir -and -not (Test-Path $outputDir)) {
                New-Item -ItemType Directory -Path $outputDir -Force | Out-Null
            }

            try {
                Invoke-ExpandOperation -InputFile $cppFile -OutputFile $outputPath -IncludeDirs $includeDirs
            } catch {
                throw "expand failed, msg: $_"
            }
        }
    }
}

Invoke-Step "Configure" {
    Set-Location $repoRoot
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
        cmake -S . -B $buildDir -G Ninja -D CMAKE_BUILD_TYPE=Release -D CP_TEMPLATE_USE_EXPANDED_TESTS=$useExpandedTests -D CP_TEMPLATE_OPTIMIZE_LEVEL=$OptimizeLevel
    } else {
        cmake -S . -B $buildDir -G Ninja -D CMAKE_BUILD_TYPE=Release -D CP_TEMPLATE_USE_EXPANDED_TESTS=$useExpandedTests -D CP_TEMPLATE_OPTIMIZE_LEVEL=$OptimizeLevel -D CMAKE_C_COMPILER=$cc -D CMAKE_CXX_COMPILER=$cxx
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

Set-Location $prevLocation
