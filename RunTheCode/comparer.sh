# 请根据实际的C++版本修改-std版本
g++ generator.cpp -o generator.out -std=c++20 -O2 || exit 1
g++ solution.cpp -o solution.out -std=c++20 -O2 || exit 1
g++ brute_force.cpp -o brute_force.out -std=c++20 -O2 || exit 1
mkdir -p testcases
count=1
while true; do
	echo "Running test $count"
	./generator.out > testcases/input.txt
	timeout 2s ./solution.out < testcases/input.txt > testcases/output_solution.txt
	exit_code=$?
	if [ $exit_code -eq 124 ]; then
		echo -e "\033[31mTime Limit Exceeded on solution\033[0m"
		break
	elif [ $exit_code -eq 139 ]; then
		echo -e "\033[31mRuntime Error (Segmentation fault) on solution\033[0m"
		cat testcases/input.txt
		break
	elif [ $exit_code -eq 134 ]; then
		echo -e "\033[31mRuntime Error (Aborted) on solution\033[0m"
		cat testcases/input.txt
		break
	elif [ $exit_code -eq 136 ]; then
		echo -e "\033[31mRuntime Error (Floating point exception) on solution\033[0m"
		cat testcases/input.txt
		break
	fi
	timeout 2s ./brute_force.out < testcases/input.txt > testcases/output_brute_force.txt
	if [ $exit_code -eq 124 ]; then
		echo -e "\033[31mTime Limit Exceeded on brute force\033[0m"
		break
	fi
	if ! diff -wB testcases/output_solution.txt testcases/output_brute_force.txt > /dev/null; then
		echo -e "\033[31mWrong Answer on test case $count\033[0m"
		echo "Input:"
		cat testcases/input.txt
		echo -e "\nSolution output:"
		cat testcases/output_solution.txt
		echo -e "\nBrute force output:"
		cat testcases/output_brute_force.txt
		break
	fi
	echo -e "\033[32mAccepted\033[0m"
	((count++))
done