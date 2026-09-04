#!/usr/bin/env bash
g++ -std=c++20 -O2 -DLOCAL $1.cpp -o $1
ulimit -s unlimited
if [[ -z $2 ]]; then
    ./$1
else
    ./$1 < $2
fi
