#include "comb.h"
#include "../test.h"

constexpr ll mod = 998244353;
using CombT = Comb<mod>;

TEST(comb_binom_basic) {
	ENSURE(CombT::binom(0, 0) == 1);
	ENSURE(CombT::binom(1, 0) == 1);
	ENSURE(CombT::binom(1, 1) == 1);
	ENSURE(CombT::binom(5, 2) == 10);
	ENSURE(CombT::binom(6, 3) == 20);
}

TEST(comb_binom_edge_cases) {
	// Out of range
	ENSURE(CombT::binom(5, 6) == 0);
	ENSURE(CombT::binom(5, -1) == 0);
	ENSURE(CombT::binom(-1, 0) == 0);
}

TEST(comb_perm_basic) {
	ENSURE(CombT::perm(5, 0) == 1);
	ENSURE(CombT::perm(5, 1) == 5);
	ENSURE(CombT::perm(5, 2) == 20);
	ENSURE(CombT::perm(5, 5) == 120);
}

TEST(comb_perm_edge_cases) {
	ENSURE(CombT::perm(5, 6) == 0);
	ENSURE(CombT::perm(-1, 0) == 0);
}

TEST(comb_fact_basic) {
	ENSURE(CombT::fact(0) == 1);
	ENSURE(CombT::fact(1) == 1);
	ENSURE(CombT::fact(5) == 120);
	ENSURE(CombT::fact(10) == 3628800);
}

TEST(comb_binom_symmetry) {
	// C(n,k) == C(n,n-k)
	for(int n = 0; n <= 10; ++n) {
		for(int k = 0; k <= n; ++k) {
			ENSURE(CombT::binom(n, k) == CombT::binom(n, n - k));
		}
	}
}

TEST(comb_pascals_identity) {
	// C(n,k) = C(n-1,k-1) + C(n-1,k) (mod modulo)
	for(int n = 2; n <= 20; ++n) {
		for(int k = 1; k < n; ++k) {
			ll lhs = CombT::binom(n, k);
			ll rhs =
				(CombT::binom(n - 1, k - 1) + CombT::binom(n - 1, k)) % mod;
			ENSURE(lhs == rhs);
		}
	}
}
