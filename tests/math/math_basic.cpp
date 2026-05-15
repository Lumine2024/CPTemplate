#include "math/basic.h"
#include "../test.h"

constexpr ll modulo = 998244353;

TEST(qpow_cmp_with_brute_force) {
	for(int i = 1; i < 100; ++i) {
		for(int j = 1; j < 100; ++j) {
			ll res_qpow = qpow<modulo>(i, j);
			ll res_brute_force = 1;
			for(int k = 0; k < j; ++k) {
				res_brute_force = res_brute_force * i % modulo;
			}
			ENSURE(res_qpow == res_brute_force);
		}
	}
}

TEST(qpow_edge_cases) {
	ENSURE(qpow<modulo>(2, 0) == 1);
	ENSURE(qpow<modulo>(0, 0) == 1);
	ENSURE(qpow<modulo>(0, 5) == 0);
	ENSURE(qpow<modulo>(1, 123456789) == 1);
	ENSURE(qpow<modulo>(modulo, 7) == 0);
	ENSURE(qpow<modulo>(modulo + 2, 10) == qpow<modulo>(2, 10));
}

TEST(qpow_fermat_identity) {
	for(int a = 1; a <= 1000; ++a) {
		ENSURE(qpow<modulo>(a, modulo - 1) == 1);
	}
}

TEST(ipow_basic_cases) {
	ENSURE(ipow(2, 0) == 1);
	ENSURE(ipow(3, 4) == 81);
	ENSURE(ipow(5, 1) == 5);
}
