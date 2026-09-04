param($name, $inp = '')
g++ "$name.cpp" -o "$name.exe" -std=c++20 -O2 "-Wl,--stack,100000000" -DLOCAL
if(!$inp) {
    & "./$name.exe"
} else {
    gc "$inp" | & "./$name.exe"
}
