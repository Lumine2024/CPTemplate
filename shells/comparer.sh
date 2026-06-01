#!/usr/bin/env bash
g++ gen.cpp -o gen -std=c++20 -O2 || exit 1
g++ sol1.cpp -o sol1 -std=c++20 -O2 || exit 1
g++ sol2.cpp -o sol2 -std=c++20 -O2 || exit 1
mkdir -p tc
cnt=1
while [ $cnt -le 100000 ]; do
	echo "Running test $cnt"
	./gen > tc/input.txt
	timeout 2s ./sol1 < tc/input.txt > tc/sol1.txt || exit 2
	timeout 2s ./sol2 < tc/input.txt > tc/sol2.txt || exit 2
	if ! diff -wB tc/sol1.txt tc/sol2.txt > /dev/null; then
		echo -e "Wrong Answer on test case $cnt"
		echo "Input:"
		cat tc/input.txt
		echo -e "\nSol1:"
		cat tc/sol1.txt
		echo -e "\nSol2:"
		cat tc/sol2.txt
		exit 1
	fi
	echo -e "Accepted"
	((cnt++))
done
