#!/usr/bin/env pwsh

param(
    [string]$Source = "docs/板子.pre-expand.md",
    [string]$Dest = "板子.md"
)

Set-StrictMode -Version Latest
$ErrorActionPreference = "Stop"

function Remove-ManualTableOfContents {
    param(
        [Parameter(Mandatory = $true)]
        [string]$Text
    )

    $lines = $Text -split "\r?\n"
    $cleaned = [System.Collections.Generic.List[string]]::new()
    $inFence = $false
    $skipToc = $false

    foreach($line in $lines) {
        if($line -match '^```') {
            $inFence = -not $inFence
        }

        if(-not $inFence -and -not $skipToc -and $line -match '^##\s+目录\s*$') {
            $skipToc = $true
            continue
        }

        if($skipToc) {
            if(-not $inFence -and $line -match '^##\s+') {
                while($cleaned.Count -gt 0 -and [string]::IsNullOrWhiteSpace($cleaned[$cleaned.Count - 1])) {
                    $cleaned.RemoveAt($cleaned.Count - 1)
                }
                $skipToc = $false
            }
            else {
                continue
            }
        }

        $cleaned.Add($line)
    }

    while($cleaned.Count -gt 0 -and [string]::IsNullOrWhiteSpace($cleaned[$cleaned.Count - 1])) {
        $cleaned.RemoveAt($cleaned.Count - 1)
    }

    return ($cleaned -join [Environment]::NewLine)
}

function Get-MarkdownAnchor {
    param(
        [Parameter(Mandatory = $true)]
        [string]$Heading,
        [Parameter(Mandatory = $true)]
        [hashtable]$SlugCounts
    )

    $builder = [System.Text.StringBuilder]::new()
    $lastWasDash = $false
    foreach($ch in $Heading.ToLowerInvariant().ToCharArray()) {
        if([char]::IsWhiteSpace($ch)) {
            if(-not $lastWasDash -and $builder.Length -gt 0) {
                [void]$builder.Append('-')
                $lastWasDash = $true
            }
            continue
        }
        if([char]::IsLetterOrDigit($ch)) {
            [void]$builder.Append($ch)
            $lastWasDash = $false
            continue
        }
        if($ch -eq '-') {
            if(-not $lastWasDash -and $builder.Length -gt 0) {
                [void]$builder.Append($ch)
                $lastWasDash = $true
            }
        }
    }

    $slug = $builder.ToString().Trim('-')
    if([string]::IsNullOrEmpty($slug)) {
        $slug = 'section'
    }

    if($SlugCounts.ContainsKey($slug)) {
        $SlugCounts[$slug]++
        return "$slug-$($SlugCounts[$slug])"
    }

    $SlugCounts[$slug] = 0
    return $slug
}

function New-TableOfContents {
    param(
        [Parameter(Mandatory = $true)]
        [string]$Text
    )

    $lines = $Text -split "\r?\n"
    $toc = [System.Collections.Generic.List[string]]::new()
    $toc.Add('## 目录')
    $toc.Add('')

    $slugCounts = @{}
    $inFence = $false
    $seenSection = $false

    foreach($line in $lines) {
        if($line -match '^```') {
            $inFence = -not $inFence
            continue
        }
        if($inFence) {
            continue
        }
        if($line -notmatch '^(##|###)\s+(.+?)\s*$') {
            continue
        }

        $marks = $Matches[1]
        $title = $Matches[2].Trim()
        if($title -eq '目录') {
            continue
        }

        $anchor = Get-MarkdownAnchor -Heading $title -SlugCounts $slugCounts
        if($marks.Length -eq 2) {
            if($seenSection) {
                $toc.Add('')
            }
            $toc.Add("[$title](#$anchor)")
            $seenSection = $true
        }
        else {
            $toc.Add("- [$title](#$anchor)")
        }
    }

    return ($toc -join [Environment]::NewLine)
}

function Add-TableOfContents {
    param(
        [Parameter(Mandatory = $true)]
        [string]$Text,
        [Parameter(Mandatory = $true)]
        [string]$TableOfContents
    )

    $lines = $Text -split "\r?\n"
    $titleIndex = -1
    for($i = 0; $i -lt $lines.Count; $i++) {
        if($lines[$i] -match '^#\s+') {
            $titleIndex = $i
            break
        }
    }

    if($titleIndex -eq -1) {
        return "$TableOfContents$([Environment]::NewLine)$([Environment]::NewLine)$Text"
    }

    $before = $lines[0..$titleIndex] -join [Environment]::NewLine
    $afterStart = $titleIndex + 1
    while($afterStart -lt $lines.Count -and [string]::IsNullOrWhiteSpace($lines[$afterStart])) {
        $afterStart++
    }

    if($afterStart -ge $lines.Count) {
        return "$before$([Environment]::NewLine)$([Environment]::NewLine)$TableOfContents"
    }

    $after = $lines[$afterStart..($lines.Count - 1)] -join [Environment]::NewLine
    return "$before$([Environment]::NewLine)$([Environment]::NewLine)$TableOfContents$([Environment]::NewLine)$([Environment]::NewLine)$after"
}

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
$content = Remove-ManualTableOfContents -Text $content
$tableOfContents = New-TableOfContents -Text $content
$content = Add-TableOfContents -Text $content -TableOfContents $tableOfContents

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
