#!/usr/bin/env pwsh

Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

. (Join-Path $PSScriptRoot 'expand.operation.ps1')

function Write-Help {
    Write-Host "Usage: ./pwsh/expand.ps1 <input_file> [-o <output_file>] [-I <include_dir>]"
    exit 1
}

$inputPath = $null
$output = $null
$includeDirs = [System.Collections.Generic.List[string]]::new()

for($idx = 0; $idx -lt $args.Count; $idx++) {
    $arg = [string]$args[$idx]
    switch($arg) {
        '-o' {
            if($idx + 1 -ge $args.Count) {
                throw "Missing value for -o"
            }
            $idx++
            $output = [string]$args[$idx]
            continue
        }
        '--output' {
            if($idx + 1 -ge $args.Count) {
                throw "Missing value for --output"
            }
            $idx++
            $output = [string]$args[$idx]
            continue
        }
        '-I' {
            if($idx + 1 -ge $args.Count) {
                throw "Missing value for -I"
            }
            $idx++
            $includeDirs.Add([string]$args[$idx])
            continue
        }
        '--include-dir' {
            if($idx + 1 -ge $args.Count) {
                throw "Missing value for --include-dir"
            }
            $idx++
            $includeDirs.Add([string]$args[$idx])
            continue
        }
        '-h' {
            Write-Help
        }
        '--help' {
            Write-Help
        }
        default {
            if($arg.StartsWith('-')) {
                throw "Unknown argument: $arg"
            }
            if($null -ne $inputPath) {
                throw "Unexpected extra positional argument: $arg"
            }
            $inputPath = $arg
            continue
        }
    }
}

if([string]::IsNullOrWhiteSpace($inputPath)) {
    Write-Help
}

$repoRoot = [System.IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..'))
$defaultIncludeDirs = @(
    (Join-Path $repoRoot 'include')
    $repoRoot
)

$allIncludeDirs = [System.Collections.Generic.List[string]]::new()
foreach($d in $includeDirs) {
    if(-not [string]::IsNullOrWhiteSpace($d)) {
        $allIncludeDirs.Add($d)
    }
}
foreach($d in $defaultIncludeDirs) {
    if(-not [string]::IsNullOrWhiteSpace($d)) {
        $allIncludeDirs.Add($d)
    }
}

Invoke-ExpandOperation -InputFile $inputPath -OutputFile $output -IncludeDirs $allIncludeDirs
