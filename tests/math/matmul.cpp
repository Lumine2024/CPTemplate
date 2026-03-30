#include "matmul.h"
#include "../test.h"

TEST(matmul_identity) {
	vector<vector<ll>> I = {{1, 0}, {0, 1}};
	vector<vector<ll>> A = {{3, 4}, {5, 6}};
	auto AI = matmul(A, I);
	ENSURE(AI[0][0] == 3);
	ENSURE(AI[0][1] == 4);
	ENSURE(AI[1][0] == 5);
	ENSURE(AI[1][1] == 6);
}

TEST(matmul_basic_2x2) {
	// [[1,2],[3,4]] * [[5,6],[7,8]] = [[19,22],[43,50]]
	vector<vector<ll>> A = {{1, 2}, {3, 4}};
	vector<vector<ll>> B = {{5, 6}, {7, 8}};
	auto C = matmul(A, B);
	ENSURE(C[0][0] == 19);
	ENSURE(C[0][1] == 22);
	ENSURE(C[1][0] == 43);
	ENSURE(C[1][1] == 50);
}

TEST(matmul_non_square) {
	// 2x3 * 3x2 = 2x2
	vector<vector<ll>> A = {{1, 2, 3}, {4, 5, 6}};
	vector<vector<ll>> B = {{7, 8}, {9, 10}, {11, 12}};
	auto C = matmul(A, B);
	// C[0][0] = 1*7+2*9+3*11 = 7+18+33 = 58
	// C[0][1] = 1*8+2*10+3*12 = 8+20+36 = 64
	// C[1][0] = 4*7+5*9+6*11 = 28+45+66 = 139
	// C[1][1] = 4*8+5*10+6*12 = 32+50+72 = 154
	ENSURE(C.size() == 2);
	ENSURE(C[0].size() == 2);
	ENSURE(C[0][0] == 58);
	ENSURE(C[0][1] == 64);
	ENSURE(C[1][0] == 139);
	ENSURE(C[1][1] == 154);
}

TEST(matpow_fibonacci) {
	// Fibonacci via matrix exponentiation:
	// [[1,1],[1,0]]^n gives F(n+1) at [0][0]
	vector<vector<ll>> fib = {{1, 1}, {1, 0}};
	auto m1 = matpow(fib, 1);
	ENSURE(m1[0][0] == 1); // F(2)=1
	auto m5 = matpow(fib, 5);
	ENSURE(m5[0][0] == 8); // F(6)=8
	auto m9 = matpow(fib, 9);
	ENSURE(m9[0][0] == 55); // F(10)=55
}

TEST(matpow_identity_power) {
	vector<vector<ll>> A = {{2, 3}, {1, 4}};
	auto A0 = matpow(A, 0);
	// A^0 = I
	ENSURE(A0[0][0] == 1);
	ENSURE(A0[0][1] == 0);
	ENSURE(A0[1][0] == 0);
	ENSURE(A0[1][1] == 1);
}
