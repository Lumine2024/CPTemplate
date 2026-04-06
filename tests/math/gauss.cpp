#include "math/gauss.h"
#include "../test.h"

constexpr ll mod = 998244353;

TEST(gauss_identity) {
	// I*x = b → x = b
	auto sol = gauss<mod>({{1, 0}, {0, 1}}, {{5}, {7}});
	ENSURE(sol.has_value());
	ENSURE((*sol)[0][0] == 5);
	ENSURE((*sol)[1][0] == 7);
}

TEST(gauss_simple_2x2) {
	// 2x+y=5, x+3y=10 → x=1, y=3
	auto sol = gauss<mod>({{2, 1}, {1, 3}}, {{5}, {10}});
	ENSURE(sol.has_value());
	ENSURE((*sol)[0][0] == 1);
	ENSURE((*sol)[1][0] == 3);
}

TEST(gauss_solution_check) {
	// Verify Ax=b for a 3x3 system
	// A = [[1,2,3],[4,5,6],[7,8,10]], b = [1,2,3] → solve modulo p
	// x ≡ solution (mod p), verify A*x ≡ b (mod p)
	vector<vector<ll>> A = {{1, 2, 3}, {4, 5, 6}, {7, 8, 10}};
	vector<vector<ll>> b = {{1}, {2}, {3}};
	auto sol = gauss<mod>(A, b);
	ENSURE(sol.has_value());
	for(int i = 0; i < 3; ++i) {
		ll val = 0;
		for(int j = 0; j < 3; ++j) {
			val = (val + A[i][j] * (*sol)[j][0]) % mod;
		}
		ENSURE(val == b[i][0]);
	}
}

TEST(gauss_no_solution) {
	// Inconsistent: x+y=1, x+y=2 → no solution
	auto sol = gauss<mod>({{1, 1}, {1, 1}}, {{1}, {2}});
	ENSURE(!sol.has_value());
}

TEST(gauss_underdetermined) {
	// Free variable: x+y=3, 2x+2y=6 → underdetermined
	auto sol = gauss<mod>({{1, 1}, {2, 2}}, {{3}, {6}});
	ENSURE(!sol.has_value());
}
