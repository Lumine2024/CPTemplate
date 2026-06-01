#include "math/sterling.h"
#include "doctest.h"

constexpr ll mod = 998244353;
using Ster = Sterling<64, mod>;

TEST_CASE("sterling_known_small_values") {
	REQUIRE(Ster::get(0, 0) == 1);
	REQUIRE(Ster::get(1, 0) == 0);
	REQUIRE(Ster::get(1, 1) == 1);
	REQUIRE(Ster::get(4, 2) == 7);
	REQUIRE(Ster::get(5, 3) == 25);
	REQUIRE(Ster::get(6, 4) == 65);
}

TEST_CASE("sterling_edge_cases") {
	REQUIRE(Ster::get(5, 6) == 0);
	REQUIRE(Ster::get(5, -1) == 0);
	REQUIRE(Ster::get(-1, 0) == 0);
	REQUIRE(Ster::get(63, 63) == 1);
	REQUIRE(Ster::get(64, 1) == 0);
}

TEST_CASE("sterling_recurrence") {
	for(int n = 1; n <= 20; ++n) {
		for(int k = 1; k <= n; ++k) {
			ll lhs = Ster::get(n, k);
			ll rhs =
				(Ster::get(n - 1, k - 1) + ll(k) * Ster::get(n - 1, k)) % mod;
			REQUIRE(lhs == rhs);
		}
	}
}
