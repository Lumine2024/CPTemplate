#include "preppow.h"
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

TEST(qpow_cmp_with_preppow) {
	for(int i = 1; i < 100; ++i) {
		PreprocessedPow<modulo> obj(i, 1000);
		for(int j = 1; j < 100; ++j) {
			ll res_qpow = qpow<modulo>(i, j);
			ll res_preppow = obj.pow(j);
			ENSURE(res_qpow == res_preppow);
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

TEST(preppow_interface_consistency) {
	PreprocessedPow<modulo> obj(37, 200000);
	for(int e = 0; e <= 200000; e += 137) {
		ll ans = obj.pow(e);
		ENSURE(ans == obj(e));
		ENSURE(ans == obj[e]);
		ENSURE(ans == qpow<modulo>(37, e));
	}
}

TEST(preppow_boundary_exponent) {
	constexpr int maxn = 500000;
	PreprocessedPow<modulo> obj(1234567, maxn);
	ENSURE(obj.pow(0) == 1);
	ENSURE(obj.pow(maxn) == qpow<modulo>(1234567, maxn));
	ENSURE(obj.pow(maxn - 1) == qpow<modulo>(1234567, maxn - 1));
}