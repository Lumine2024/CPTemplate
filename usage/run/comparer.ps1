function compile($file, $out) {
    g++ $file -o $out -std=c++20 -O2 -Wall
    if($LASTEXITCODE -ne 0) {
        Write-Host "compile error $file" -ForegroundColor Red
        exit 1
    }
}
function check2($msg) {
    if($LASTEXITCODE -ne 0) {
        Write-Host "Runtime error: $msg, exit code is $LASTEXITCODE" -ForegroundColor Red
        exit 2
    }
}
compile "generator.cpp" "gen.exe"
compile "brute_force.cpp" "bf.exe"
compile "solution.cpp" "sol.exe"
mkdir -p testcases -Force
$cnt = 1
while($cnt -le 100000) {
    Write-Host "Running test case $cnt"
    ./gen.exe > "testcases/input.txt"
    check2 "generator"
    Get-Content "testcases/input.txt" | ./sol.exe > "testcases/sol.out"
    check2 "solution"
    Get-Content "testcases/input.txt" | ./bf.exe > "testcases/bf.out"
    check2 "brute_force"
    $f1 = (Get-Content "testcases/sol.out" -Raw) -replace '\s+', ''
    $f2 = (Get-Content "testcases/bf.out" -Raw) -replace '\s+', ''
    if($f1 -ne $f2) {
        Write-Host "Wrong answer on $cnt" -ForegroundColor Red
        Write-Host "Input:"
        Get-Content "testcases/input.txt"
        Write-Host "Solution output:"
        Get-Content "testcases/sol.out"
        Write-Host "Brute force output:"
        Get-Content "testcases/bf.out"
        exit 3
    }
    Write-Host "Accepted" -ForegroundColor Green
    $cnt++
}