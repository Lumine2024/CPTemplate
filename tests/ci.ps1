param(
    [Parameter(Mandatory = $true)]
    [string]$Compiler
)

$ErrorActionPreference = 'Stop'

function Invoke-Step([string]$name, [scriptblock]$body) {
    Write-Host "[CI] ==> $name"
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

Invoke-Step "Configure" {
    cmake -S . -B $buildDir -G Ninja -D CMAKE_BUILD_TYPE=Release -D CMAKE_C_COMPILER=$cc -D CMAKE_CXX_COMPILER=$cxx
}
Invoke-Step "build" {
    cmake --build $buildDir -j
}
Invoke-Step "test" {
    ctest --test-dir $buildDir --output-on-failure
}