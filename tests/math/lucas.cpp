#include "math/lucas.h"
#include "doctest.h"

static int binom_mod_prime_small(int n, int k, int p) {
	if(k < 0 || k > n) return 0;
	vector<vector<int>> c(n + 1, vector<int>(k + 1, 0));
	c[0][0] = 1;
	for(int i = 1; i <= n; ++i) {
		c[i][0] = 1;
		for(int j = 1; j <= min(i, k); ++j) {
			c[i][j] = c[i - 1][j];
			c[i][j] += c[i - 1][j - 1];
			c[i][j] %= p;
		}
	}
	return c[n][k];
}

TEST_CASE("lucas_small_matches_pascal_mod7") {
	for(int n = 0; n <= 25; ++n) {
		for(int k = 0; k <= n; ++k) {
			REQUIRE(Lucas<7>::binom(n, k) == binom_mod_prime_small(n, k, 7));
		}
	}
}

TEST_CASE("lucas_handles_k_out_of_range") {
	REQUIRE(Lucas<11>::binom(5, 6) == 0);
	REQUIRE(Lucas<11>::binom(0, 1) == 0);
}

TEST_CASE("lucas_large_numbers_digit_decomposition") {
	// 100(base7)=202, 20(base7)=26 => C(100,20) mod 7 = C(2,0)*C(0,2)*C(2,6)=0
	REQUIRE(Lucas<7>::binom(100, 20) == 0);
	// 58(base7)=112, 9(base7)=12 => C(58,9) mod 7 = C(1,0)*C(1,1)*C(2,2)=1
	REQUIRE(Lucas<7>::binom(58, 9) == 1);
}
