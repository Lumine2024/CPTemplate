#include "comb.h"
#include "../test.h"

TEST(comb_binom_basic) {
	ENSURE(Comb::binom(0, 0) == 1);
	ENSURE(Comb::binom(1, 0) == 1);
	ENSURE(Comb::binom(1, 1) == 1);
	ENSURE(Comb::binom(5, 2) == 10);
	ENSURE(Comb::binom(6, 3) == 20);
}

TEST(comb_binom_edge_cases) {
	// Out of range
	ENSURE(Comb::binom(5, 6) == 0);
	ENSURE(Comb::binom(5, -1) == 0);
	ENSURE(Comb::binom(-1, 0) == 0);
}

TEST(comb_perm_basic) {
	ENSURE(Comb::perm(5, 0) == 1);
	ENSURE(Comb::perm(5, 1) == 5);
	ENSURE(Comb::perm(5, 2) == 20);
	ENSURE(Comb::perm(5, 5) == 120);
}

TEST(comb_perm_edge_cases) {
	ENSURE(Comb::perm(5, 6) == 0);
	ENSURE(Comb::perm(-1, 0) == 0);
}

TEST(comb_fact_basic) {
	ENSURE(Comb::fact(0) == 1);
	ENSURE(Comb::fact(1) == 1);
	ENSURE(Comb::fact(5) == 120);
	ENSURE(Comb::fact(10) == 3628800);
}

TEST(comb_binom_symmetry) {
	// C(n,k) == C(n,n-k)
	for(int n = 0; n <= 10; ++n) {
		for(int k = 0; k <= n; ++k) {
			ENSURE(Comb::binom(n, k) == Comb::binom(n, n - k));
		}
	}
}

TEST(comb_pascals_identity) {
	// C(n,k) = C(n-1,k-1) + C(n-1,k) (mod modulo)
	constexpr ll mod = 998244353;
	for(int n = 2; n <= 20; ++n) {
		for(int k = 1; k < n; ++k) {
			ll lhs = Comb::binom(n, k);
			ll rhs = (Comb::binom(n - 1, k - 1) + Comb::binom(n - 1, k)) % mod;
			ENSURE(lhs == rhs);
		}
	}
}
