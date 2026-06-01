#include "math/lagrange.h"
#include "doctest.h"

constexpr ll mod = 998244353;

TEST_CASE("lagrange_general_points") {
	vector<ll> x = {1, 3, 4};
	vector<ll> y = {6, 18, 27}; // f(x) = x^2 + 2x + 3
	REQUIRE(lagrange<mod>(x, y, 5) == 38);
}

TEST_CASE("lagrange_consecutive_points") {
	vector<ll> y = {3, 6, 11, 18}; // f(x) = x^2 + 2x + 3
	REQUIRE(lagrange<mod>(y, 5) == 38);
}
