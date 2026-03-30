#include "catalan.h"
#include "../test.h"

constexpr ll mod = 998244353;
using Cat = Catalan<mod, 32>;

TEST(catalan_first_values) {
	vector<int> known = {1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862};
	for(int i = 0; i < (int)known.size(); ++i) {
		ENSURE(Cat::get(i) == known[i]);
	}
}

TEST(catalan_recurrence_small_n) {
	for(int n = 0; n <= 20; ++n) {
		ll lhs = Cat::get(n + 1);
		ll rhs = (ll)Cat::get(n) * (4 * n + 2) % mod;
		rhs = rhs * qpow<mod>(n + 2, mod - 2) % mod;
		ENSURE(lhs == rhs);
	}
}
