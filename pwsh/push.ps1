#!/usr/bin/env pwsh

param(
    [Parameter(Mandatory = $true)]
    [string]$Message
)

$prevLocation = Get-Location

Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

function Test-LastExitCode([string]$msg) {
    if($LASTEXITCODE -ne 0) {
        throw $msg
    }
}

Set-Location (Join-Path $PSScriptRoot "..")

# simulate .github/workflows/ci.yml's workflow to ensure passing CI
# TODO: It's serial, not parallel
foreach($optimizeLevel in @(0, 1, 2)) {
    foreach($compiler in @("gcc", "clang", "msvc", "clang-cl")) {
        Write-Output "Running CI with compiler $compiler and optimize level $optimizeLevel"
        Write-Output "CI with expand"
        ./pwsh/ci.ps1 -Compiler $compiler -OptimizeLevel $optimizeLevel -TestWithExpand | Out-Null
        Test-LastExitCode "CI with expand failed"
        Write-Output "CI without expand"
        ./pwsh/ci.ps1 -Compiler $compiler -OptimizeLevel $optimizeLevel -TestWithoutExpand | Out-Null
        Test-LastExitCode "CI without expand failed"
    }
}

# expand banzi
./pwsh/expand_banzi.ps1

# invoke git operations
git add .
git commit -m $Message
git push

Set-Location $prevLocation