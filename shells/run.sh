#!/usr/bin/env bash
g++ -std=c++20 -O2 -DLOCAL $1.cpp -o $1
./$1
rm -rf $1
