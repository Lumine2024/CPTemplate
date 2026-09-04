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

Push-Location $repoRoot
try {
    if($TestWithExpand) {
        Invoke-Step "Expand" {
            $testsRoot = Join-Path $repoRoot "tests"
            $expandedDir = Join-Path $testsRoot "expanded"
            Push-Location $testsRoot
            try {
                if(Test-Path $expandedDir) {
                    Remove-Item -LiteralPath $expandedDir -Recurse -Force
                }
                New-Item -ItemType Directory -Path $expandedDir -Force | Out-Null
                Copy-Item -Path "expanded_cmakelists.txt" -Destination (Join-Path $expandedDir "CMakeLists.txt")
                $includeRoot = Join-Path $repoRoot "include"
                [string[]]$includeDirs = @((Resolve-Path $includeRoot).Path, (Resolve-Path (Join-Path $testsRoot "doctest")).Path)
                [string[]]$cppFiles = @(
                    Get-ChildItem -Recurse -File -Filter "*.cpp" -Path . | ForEach-Object {
                        $relativePath = [System.IO.Path]::GetRelativePath((Resolve-Path ".").Path, $_.FullName)
                        if(($relativePath -split '[\\/]') -contains 'expanded') {
                            return
                        }
                        $relativePath
                    }
                )
                $expandOperationScript = Join-Path $repoRoot "pwsh/expand.operation.ps1"
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
            } finally {
                Pop-Location
            }
        }
    }

    Invoke-Step "Configure" {
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
} finally {
    Pop-Location
}
