#include "math/comb.h"
#include "doctest.h"

constexpr ll mod = 998244353;
using CombT = Comb<mod>;

TEST_CASE("comb_binom_basic") {
	REQUIRE(CombT::binom(0, 0) == 1);
	REQUIRE(CombT::binom(1, 0) == 1);
	REQUIRE(CombT::binom(1, 1) == 1);
	REQUIRE(CombT::binom(5, 2) == 10);
	REQUIRE(CombT::binom(6, 3) == 20);
}

TEST_CASE("comb_binom_edge_cases") {
	// Out of range
	REQUIRE(CombT::binom(5, 6) == 0);
	REQUIRE(CombT::binom(5, -1) == 0);
	REQUIRE(CombT::binom(-1, 0) == 0);
}

TEST_CASE("comb_perm_basic") {
	REQUIRE(CombT::perm(5, 0) == 1);
	REQUIRE(CombT::perm(5, 1) == 5);
	REQUIRE(CombT::perm(5, 2) == 20);
	REQUIRE(CombT::perm(5, 5) == 120);
}

TEST_CASE("comb_perm_edge_cases") {
	REQUIRE(CombT::perm(5, 6) == 0);
	REQUIRE(CombT::perm(-1, 0) == 0);
}

TEST_CASE("comb_fact_basic") {
	REQUIRE(CombT::fact(0) == 1);
	REQUIRE(CombT::fact(1) == 1);
	REQUIRE(CombT::fact(5) == 120);
	REQUIRE(CombT::fact(10) == 3628800);
}

TEST_CASE("comb_binom_symmetry") {
	// C(n,k) == C(n,n-k)
	for(int n = 0; n <= 10; ++n) {
		for(int k = 0; k <= n; ++k) {
			REQUIRE(CombT::binom(n, k) == CombT::binom(n, n - k));
		}
	}
}

TEST_CASE("comb_pascals_identity") {
	// C(n,k) = C(n-1,k-1) + C(n-1,k) (mod modulo)
	for(int n = 2; n <= 20; ++n) {
		for(int k = 1; k < n; ++k) {
			ll lhs = CombT::binom(n, k);
			ll rhs =
				(CombT::binom(n - 1, k - 1) + CombT::binom(n - 1, k)) % mod;
			REQUIRE(lhs == rhs);
		}
	}
}
