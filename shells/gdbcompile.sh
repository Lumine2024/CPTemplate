#!/usr/bin/env bash
g++ -std=c++20 -O0 -g $1.cpp -o $1
gdb ./1
