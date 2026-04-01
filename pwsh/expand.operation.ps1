#!/usr/bin/env pwsh

Set-StrictMode -Version Latest

function Invoke-ExpandOperation {
    [CmdletBinding()]
    param(
        [Parameter(Mandatory = $true)]
        [string]$InputFile,

        [Parameter()]
        [string]$OutputFile,

        [Parameter()]
        [string[]]$IncludeDirs = @()
    )

    function Resolve-NormalizedPath {
        param(
            [Parameter(Mandatory = $true)]
            [string]$PathValue
        )

        if([System.IO.Path]::IsPathRooted($PathValue)) {
            return [System.IO.Path]::GetFullPath($PathValue)
        }
        return [System.IO.Path]::GetFullPath((Join-Path (Get-Location).Path $PathValue))
    }

    $quotedIncludePattern = [regex]'\s*#include\s+"([^"]+)"'
    $pragmaOncePattern = [regex]'\s*#pragma\s+once\s*$'
    $included = [System.Collections.Generic.HashSet[string]]::new([System.StringComparer]::OrdinalIgnoreCase)

    $normalizedIncludeDirs = [System.Collections.Generic.List[string]]::new()
    foreach($dir in $IncludeDirs) {
        $normalized = Resolve-NormalizedPath -PathValue $dir
        if(-not (Test-Path -LiteralPath $normalized -PathType Container)) {
            throw "Include directory does not exist: $dir"
        }
        $normalizedIncludeDirs.Add($normalized)
    }

    function Expand-FileInternal {
        param(
            [Parameter(Mandatory = $true)]
            [string]$FilePath
        )

        $absPath = Resolve-NormalizedPath -PathValue $FilePath
        if(-not (Test-Path -LiteralPath $absPath -PathType Leaf)) {
            throw "Error: file not found: $absPath"
        }

        if(-not $included.Add($absPath)) {
            return ""
        }

        $builder = [System.Text.StringBuilder]::new()
        $fileDir = Split-Path -Parent $absPath
        $lines = [System.IO.File]::ReadLines($absPath)

        foreach($line in $lines) {
            if($pragmaOncePattern.IsMatch($line)) {
                continue
            }

            $match = $quotedIncludePattern.Match($line)
            if($match.Success) {
                $includePath = $match.Groups[1].Value
                $candidate = Resolve-NormalizedPath -PathValue (Join-Path $fileDir $includePath)
                $resolvedInclude = $null

                if(Test-Path -LiteralPath $candidate -PathType Leaf) {
                    $resolvedInclude = $candidate
                }
                else {
                    foreach($incDir in $normalizedIncludeDirs) {
                        $incCandidate = Resolve-NormalizedPath -PathValue (Join-Path $incDir $includePath)
                        if(Test-Path -LiteralPath $incCandidate -PathType Leaf) {
                            $resolvedInclude = $incCandidate
                            break
                        }
                    }
                }

                if($null -eq $resolvedInclude) {
                    throw "Cannot resolve include '$includePath' from '$absPath'"
                }

                $expanded = Expand-FileInternal -FilePath $resolvedInclude
                if(-not [string]::IsNullOrEmpty($expanded)) {
                    [void]$builder.Append($expanded)
                }
                continue
            }

            [void]$builder.AppendLine($line)
        }

        return $builder.ToString()
    }

    $inputAbs = Resolve-NormalizedPath -PathValue $InputFile
    if(-not (Test-Path -LiteralPath $inputAbs -PathType Leaf)) {
        throw "Error: '$InputFile' is not a file or does not exist."
    }

    $expandedText = Expand-FileInternal -FilePath $inputAbs

    if([string]::IsNullOrWhiteSpace($OutputFile)) {
        Write-Output $expandedText
        return
    }

    $outputAbs = Resolve-NormalizedPath -PathValue $OutputFile
    $outputDir = Split-Path -Parent $outputAbs
    if(-not [string]::IsNullOrEmpty($outputDir)) {
        New-Item -ItemType Directory -Path $outputDir -Force | Out-Null
    }

    [System.IO.File]::WriteAllText($outputAbs, $expandedText, [System.Text.Encoding]::UTF8)
    Write-Output "Expanded output written to: $outputAbs"
}
