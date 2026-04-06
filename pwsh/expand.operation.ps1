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
        if(Test-Path -LiteralPath $normalized -PathType Container) {
            $normalizedIncludeDirs.Add($normalized)
        }
    }

    $includeFileNameIndex = @{}
    foreach($incDir in $normalizedIncludeDirs) {
        Get-ChildItem -Path $incDir -Recurse -File | ForEach-Object {
            $name = $_.Name
            if(-not $includeFileNameIndex.ContainsKey($name)) {
                $includeFileNameIndex[$name] = [System.Collections.Generic.List[string]]::new()
            }
            $includeFileNameIndex[$name].Add($_.FullName)
        }
    }

    function Resolve-IncludeByFileName {
        param(
            [Parameter(Mandatory = $true)]
            [string]$IncludePath
        )

        if($IncludePath -match '[\\/]') {
            return $null
        }
        if(-not $includeFileNameIndex.ContainsKey($IncludePath)) {
            return $null
        }

        $candidates = $includeFileNameIndex[$IncludePath]
        if($candidates.Count -eq 1) {
            return $candidates[0]
        }

        throw "Ambiguous include '$IncludePath' resolved to multiple files: $($candidates -join ', ')"
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
                    if($null -eq $resolvedInclude) {
                        $resolvedInclude = Resolve-IncludeByFileName -IncludePath $includePath
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
