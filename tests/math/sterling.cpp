#include "math/sterling.h"
#include "../test.h"

constexpr ll mod = 998244353;
using Ster = Sterling<64, mod>;

TEST(sterling_known_small_values) {
	ENSURE(Ster::get(0, 0) == 1);
	ENSURE(Ster::get(1, 0) == 0);
	ENSURE(Ster::get(1, 1) == 1);
	ENSURE(Ster::get(4, 2) == 7);
	ENSURE(Ster::get(5, 3) == 25);
	ENSURE(Ster::get(6, 4) == 65);
}

TEST(sterling_edge_cases) {
	ENSURE(Ster::get(5, 6) == 0);
	ENSURE(Ster::get(5, -1) == 0);
	ENSURE(Ster::get(-1, 0) == 0);
	ENSURE(Ster::get(63, 63) == 1);
	ENSURE(Ster::get(64, 1) == 0);
}

TEST(sterling_recurrence) {
	for(int n = 1; n <= 20; ++n) {
		for(int k = 1; k <= n; ++k) {
			ll lhs = Ster::get(n, k);
			ll rhs =
				(Ster::get(n - 1, k - 1) + ll(k) * Ster::get(n - 1, k)) % mod;
			ENSURE(lhs == rhs);
		}
	}
}
