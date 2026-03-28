#!/usr/bin/env bash
g++ -std=c++20 -Og -g $1.cpp -o $1
gdb -x inst.gdb ./1
