#include "math/basic.h"
#include "doctest.h"

constexpr ll modulo = 998244353;

TEST_CASE("qpow_cmp_with_brute_force") {
	for(int i = 1; i < 100; ++i) {
		for(int j = 1; j < 100; ++j) {
			ll res_qpow = qpow<modulo>(i, j);
			ll res_brute_force = 1;
			for(int k = 0; k < j; ++k) {
				res_brute_force = res_brute_force * i % modulo;
			}
			REQUIRE(res_qpow == res_brute_force);
		}
	}
}

TEST_CASE("qpow_edge_cases") {
	REQUIRE(qpow<modulo>(2, 0) == 1);
	REQUIRE(qpow<modulo>(0, 0) == 1);
	REQUIRE(qpow<modulo>(0, 5) == 0);
	REQUIRE(qpow<modulo>(1, 123456789) == 1);
	REQUIRE(qpow<modulo>(modulo, 7) == 0);
	REQUIRE(qpow<modulo>(modulo + 2, 10) == qpow<modulo>(2, 10));
}

TEST_CASE("qpow_fermat_identity") {
	for(int a = 1; a <= 1000; ++a) {
		REQUIRE(qpow<modulo>(a, modulo - 1) == 1);
	}
}

TEST_CASE("ipow_basic_cases") {
	REQUIRE(ipow(2, 0) == 1);
	REQUIRE(ipow(3, 4) == 81);
	REQUIRE(ipow(5, 1) == 5);
}
