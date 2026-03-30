#include "intdiv.h"
#include "../test.h"

constexpr ll mod = 998244353;

TEST(intdiv_n1) {
	// sum_{i=1}^{1} floor(1/i) = 1
	ENSURE(intdiv<mod>(1) == 1);
}

TEST(intdiv_n4) {
	// sum_{i=1}^{4} floor(4/i) = 4+2+1+1 = 8
	ENSURE(intdiv<mod>(4) == 8);
}

TEST(intdiv_n6) {
	// sum_{i=1}^{6} floor(6/i) = 6+3+2+1+1+1 = 14
	ENSURE(intdiv<mod>(6) == 14);
}

TEST(intdiv_n10) {
	// sum_{i=1}^{10} floor(10/i) = 10+5+3+2+2+1+1+1+1+1 = 27
	ENSURE(intdiv<mod>(10) == 27);
}

TEST(intdiv_brute_force) {
	// Compare with brute force for n=100
	ll expected = 0;
	for(ll i = 1; i <= 100; ++i) {
		expected = (expected + 100 / i) % mod;
	}
	ENSURE(intdiv<mod>(100) == expected);
}
