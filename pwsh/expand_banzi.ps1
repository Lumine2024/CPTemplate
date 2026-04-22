#!/usr/bin/env pwsh

param(
    [string]$Source = "docs/板子.pre-expand.md",
    [string]$Dest = "板子.md"
)

Set-StrictMode -Version Latest
$ErrorActionPreference = "Stop"

function Convert-Attributes {
    param(
        [Parameter(Mandatory = $true)]
        [string]$Text
    )

    $attrs = @{}
    $attrPattern = [regex]'(\w+)\s*=\s*(?:"([^"]*)"|''([^'']*)''|([^\s"''>]+))'
    foreach($m in $attrPattern.Matches($Text)) {
        $name = $m.Groups[1].Value
        $value = if($m.Groups[2].Success) {
            $m.Groups[2].Value
        }
        elseif($m.Groups[3].Success) {
            $m.Groups[3].Value
        }
        else {
            $m.Groups[4].Value
        }
        $attrs[$name] = $value
    }
    return $attrs
}

function Resolve-TargetPath {
    param(
        [Parameter(Mandatory = $true)]
        [string]$PathValue,
        [Parameter(Mandatory = $true)]
        [string]$BaseDir
    )

    if([System.IO.Path]::IsPathRooted($PathValue)) {
        return $PathValue
    }
    return (Join-Path $BaseDir $PathValue)
}

$sourceFull = (Resolve-Path -Path $Source).Path
$sourceDir = Split-Path -Parent $sourceFull
$content = Get-Content -Path $sourceFull -Raw -Encoding utf8

$tagPattern = [regex]'(?is)<file\s+([^>]*)>\s*</file>'
$expanded = "<!-- THIS FILE IS AUTO GENERATED, DO NOT MODIFY IT MANUALLY -->`n`n" + $tagPattern.Replace($content, {
    param($m)

    $attrs = Convert-Attributes -Text $m.Groups[1].Value
    if(-not $attrs.ContainsKey("path")) {
        throw "<file> 标签缺少 path 属性: $($m.Value)"
    }

    $targetPath = Resolve-TargetPath -PathValue $attrs["path"] -BaseDir $sourceDir
    if(-not (Test-Path -LiteralPath $targetPath -PathType Leaf)) {
        throw "引用文件不存在: $targetPath"
    }

    $lines = Get-Content -Path $targetPath -Encoding utf8
    $lineCount = $lines.Count

    $start = if($attrs.ContainsKey("rangeBegin")) { [int]$attrs["rangeBegin"] } else { 1 }
    $end = if($attrs.ContainsKey("rangeEnd")) { [int]$attrs["rangeEnd"] } else { $lineCount }

    if($lineCount -eq 0) {
        if($start -ne 1 -or $end -ne 0) {
            throw "文件为空，无法应用范围 $start..${end}: $targetPath"
        }
        $snippet = ""
    }
    else {
        if($start -lt 1 -or $end -lt $start -or $end -gt $lineCount) {
            throw "非法行范围 $start..$end (文件共 $lineCount 行): $targetPath"
        }
        $selected = $lines[($start - 1)..($end - 1)]
        $snippet = ($selected -join [Environment]::NewLine)
    }

    $lang = if($attrs.ContainsKey("type")) { $attrs["type"] } else { "" }
    if([string]::IsNullOrWhiteSpace($lang)) {
        return $snippet
    }
    return ('```{0}{1}{2}{1}```' -f $lang, [Environment]::NewLine, $snippet)
})

$destPath = Resolve-TargetPath -PathValue $Dest -BaseDir $sourceDir
$destDir = Split-Path -Parent $destPath
if(-not [string]::IsNullOrEmpty($destDir)) {
    New-Item -ItemType Directory -Path $destDir -Force | Out-Null
}

Set-Content -Path $destPath -Value $expanded -Encoding utf8
Write-Host "文件已展开至: $destPath"
