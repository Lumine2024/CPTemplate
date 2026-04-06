#include "math/ntt.h"
#include "../test.h"

TEST(ntt_multiply_basic) {
	// (1 + x) * (1 + x) = 1 + 2x + x^2
	vector<ll> a = {1, 1};
	vector<ll> b = {1, 1};
	auto c = multiply(a, b);
	ENSURE(c.size() == 3);
	ENSURE(c[0] == 1);
	ENSURE(c[1] == 2);
	ENSURE(c[2] == 1);
}

TEST(ntt_multiply_constant) {
	// 3 * (1 + 2x) = 3 + 6x
	vector<ll> a = {3};
	vector<ll> b = {1, 2};
	auto c = multiply(a, b);
	ENSURE(c.size() == 2);
	ENSURE(c[0] == 3);
	ENSURE(c[1] == 6);
}

TEST(ntt_multiply_mod) {
	// Verify result is reduced mod 998244353
	vector<ll> a = {modulo - 1};
	vector<ll> b = {modulo - 1};
	auto c = multiply(a, b);
	ENSURE(c.size() == 1);
	ENSURE(c[0] == 1); // (-1)*(-1) = 1 mod p
}

TEST(ntt_multiply_larger) {
	// (1 + x + x^2) * (1 + x) = 1 + 2x + 2x^2 + x^3
	vector<ll> a = {1, 1, 1};
	vector<ll> b = {1, 1};
	auto c = multiply(a, b);
	ENSURE(c.size() == 4);
	ENSURE(c[0] == 1);
	ENSURE(c[1] == 2);
	ENSURE(c[2] == 2);
	ENSURE(c[3] == 1);
}

TEST(ntt_multiply_zero) {
	// 0 * anything = 0
	vector<ll> a = {0, 0};
	vector<ll> b = {3, 5, 7};
	auto c = multiply(a, b);
	for(ll v : c) ENSURE(v == 0);
}
