g++ generator.cpp -o gen.out -std=c++20 -O2 || exit 1
g++ solution.cpp -o sol.out -std=c++20 -O2 -Wall || exit 1
g++ brute_force.cpp -o bf.out -std=c++20 -O2 || exit 1
mkdir -p tc
cnt=1
while true; do
	echo "Running test $cnt"
	./gen.out > tc/input.txt
	timeout 2s ./sol.out < tc/input.txt > tc/sol.txt
	exit_code=$?
	if [ $exit_code -ne 0 ]; then
		echo -e "\033[31mRuntime error or time limit exceeded on solution\033[0m"
		break
	fi
	timeout 2s ./bf.out < tc/input.txt > tc/bf.txt
	if [ $exit_code -ne 0 ]; then
		echo -e "\033[31mRuntime error or time limit exceeded on brute force\033[0m"
		break
	fi
	if ! diff -wB tc/sol.txt tc/bf.txt > /dev/null; then
		echo -e "\033[31mWrong Answer on test case $cnt\033[0m"
		echo "Input:"
		cat tc/input.txt
		echo -e "\nSolution output:"
		cat tc/sol.txt
		echo -e "\nBrute force output:"
		cat tc/bf.txt
		break
	fi
	echo -e "\033[32mAccepted\033[0m"
	((cnt++))
done