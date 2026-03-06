#!/usr/bin/env pwsh
Set-Alias println Write-Host

g++ gen.cpp -o gen -std=c++23 -O2
g++ sol.cpp -o sol -std=c++23 -O2
g++ sol2.cpp -o sol2 -std=c++23 -O2
mkdir -p tc -Force
$cnt = 1
while($cnt -le 100000) {
    println "Running $cnt"
    ./gen > "tc/input.txt"
    cat "tc/input.txt" | ./sol > "tc/sol.txt"
    cat "tc/input.txt" | ./sol2 > "tc/sol2.txt"
    $f1 = (cat "tc/sol.txt" -Raw) -replace '\s+', ''
    $f2 = (cat "tc/sol2.txt" -Raw) -replace '\s+', ''
    if($f1 -ne $f2) {
        println "Wrong answer" -ForegroundColor Red
        println "Input:"
        cat "tc/input.txt"
        println "Sol1:"
        cat "tc/sol.txt"
        println "Sol2:"
        cat "tc/sol2.txt"
        break
    }
    println "Accepted" -ForegroundColor Green
    $cnt++
}