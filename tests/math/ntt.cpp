#include "math/ntt.h"
#include "doctest.h"

constexpr ll modulo = 998244353;
using Z = ModInt<modulo>;

TEST_CASE("ntt_multiply_basic") {
	// (1 + x) * (1 + x) = 1 + 2x + x^2
	vector<Z> a = {1, 1};
	vector<Z> b = {1, 1};
	auto c = multiply<modulo>(a, b);
	REQUIRE(c.size() == 3);
	REQUIRE(c[0] == Z(1));
	REQUIRE(c[1] == Z(2));
	REQUIRE(c[2] == Z(1));
}

TEST_CASE("ntt_multiply_constant") {
	// 3 * (1 + 2x) = 3 + 6x
	vector<Z> a = {3};
	vector<Z> b = {1, 2};
	auto c = multiply<modulo>(a, b);
	REQUIRE(c.size() == 2);
	REQUIRE(c[0] == Z(3));
	REQUIRE(c[1] == Z(6));
}

TEST_CASE("ntt_multiply_mod") {
	// Verify result is reduced mod 998244353
	vector<Z> a = {modulo - 1};
	vector<Z> b = {modulo - 1};
	auto c = multiply<modulo>(a, b);
	REQUIRE(c.size() == 1);
	REQUIRE(c[0] == Z(1)); // (-1)*(-1) = 1 mod p
}

TEST_CASE("ntt_multiply_larger") {
	// (1 + x + x^2) * (1 + x) = 1 + 2x + 2x^2 + x^3
	vector<Z> a = {1, 1, 1};
	vector<Z> b = {1, 1};
	auto c = multiply<modulo>(a, b);
	REQUIRE(c.size() == 4);
	REQUIRE(c[0] == Z(1));
	REQUIRE(c[1] == Z(2));
	REQUIRE(c[2] == Z(2));
	REQUIRE(c[3] == Z(1));
}

TEST_CASE("ntt_multiply_zero") {
	// 0 * anything = 0
	vector<Z> a = {0, 0};
	vector<Z> b = {3, 5, 7};
	auto c = multiply<modulo>(a, b);
	for(ll v : c) REQUIRE(v == 0);
}
