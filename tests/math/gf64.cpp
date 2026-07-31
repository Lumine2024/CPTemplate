#include "math/gf64.h"
#include "doctest.h"

namespace {
bool get_bit(ull lo, ull hi, int pos) {
	return pos < 64 ? (lo >> pos & 1ULL) : (hi >> (pos - 64) & 1ULL);
}

void xor_bit(ull &lo, ull &hi, int pos) {
	if(pos < 64) {
		lo ^= 1ULL << pos;
	} else {
		hi ^= 1ULL << (pos - 64);
	}
}

ull gf64_mul_ref(ull a, ull b) {
	ull lo = 0, hi = 0;
	for(int i = 0; i < 64; ++i) {
		if((b >> i & 1ULL) == 0) continue;
		if(i == 0) {
			lo ^= a;
		} else {
			lo ^= a << i;
			hi ^= a >> (64 - i);
		}
	}
	for(int k = 127; k >= 64; --k) {
		if(!get_bit(lo, hi, k)) continue;
		int shift = k - 64;
		xor_bit(lo, hi, k);
		xor_bit(lo, hi, shift);
		xor_bit(lo, hi, shift + 1);
		xor_bit(lo, hi, shift + 3);
		xor_bit(lo, hi, shift + 4);
	}
	return lo;
}
} // namespace

TEST_CASE("gf64_addition_is_xor") {
	GF64 a(0x123456789abcdef0ULL), b(0xfedcba9876543210ULL);
	REQUIRE((a + b).val() == (0x123456789abcdef0ULL ^ 0xfedcba9876543210ULL));
	a += b;
	REQUIRE(a.val() == (0x123456789abcdef0ULL ^ 0xfedcba9876543210ULL));
}

TEST_CASE("gf64_multiplication_matches_reference") {
	vector<pair<ull, ull>> cases = {
		{0ULL, 0ULL},
		{0ULL, 0xdeadbeefULL},
		{1ULL, 0xfedcba9876543210ULL},
		{0x8000000000000000ULL, 2ULL},
		{0x123456789abcdef0ULL, 0xfedcba9876543210ULL},
		{0xffffffffffffffffULL, 0xffffffffffffffffULL},
	};
	for(auto [a, b] : cases) {
		REQUIRE((GF64(a) * GF64(b)).val() == gf64_mul_ref(a, b));
		REQUIRE((GF64(b) * GF64(a)).val() == gf64_mul_ref(b, a));
	}
}

TEST_CASE("gf64_inverse_and_power") {
	vector<ull> values = {
		1ULL,
		2ULL,
		3ULL,
		0x123456789abcdef0ULL,
		0xffffffffffffffffULL,
	};
	for(ull x : values) {
		GF64 a(x);
		REQUIRE((a * a.inv()).val() == 1ULL);
		REQUIRE(a.qpow(0).val() == 1ULL);
		REQUIRE(a.qpow(1).val() == a.val());
		REQUIRE(a.qpow(5).val() ==
				gf64_mul_ref(gf64_mul_ref(gf64_mul_ref(gf64_mul_ref(x, x), x), x), x));
	}
}
