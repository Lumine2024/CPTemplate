sal p Write-Host
g++ gen.cpp -o gen -std=c++23 -O2
g++ sol.cpp -o sol -std=c++23 -O2
g++ sol2.cpp -o sol2 -std=c++23 -O2
mkdir -p tc -Force
$cnt = 1
while($cnt -le 100000) {
    p "Running $cnt"
    ./gen > "tc/input.txt"
    gc "tc/input.txt" -Raw | ./sol > "tc/sol.txt"
    gc "tc/input.txt" -Raw | ./sol2 > "tc/sol2.txt"
    $f1 = (gc "tc/sol.txt" -Raw) -replace '\s+', ''
    $f2 = (gc "tc/sol2.txt" -Raw) -replace '\s+', ''
    if($f1 -ne $f2) {
        p "Wrong answer" -ForegroundColor Red
        p "Input:"
        gc "tc/input.txt" -Raw
        p "Sol1:"
        gc "tc/sol.txt" -Raw
        p "Sol2:"
        gc "tc/sol2.txt" -Raw
        break
    }
    p "Accepted" -ForegroundColor Green
    $cnt++
}
