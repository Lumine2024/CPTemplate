#pragma once
#include "math/basic.h"

template<ll modulo>
struct Lucas {
	Lucas() = delete;
	static ll binom(ll n, ll m) {
		ensure_init();
		if(m < 0 || m > n) return 0;
		if(m == 0) return 1;
		return binom(n / modulo, m / modulo) *
			   small_binom(n % modulo, m % modulo) % modulo;
	}

private:
	static inline vector<int> fact, invfact;
	static inline bool inited = false;

	static ll small_binom(int n, int m) {
		if(m < 0 || m > n) return 0;
		return ll(fact[n]) * ll(invfact[m]) % modulo * ll(invfact[n - m]) %
			   modulo;
	}
	static void ensure_init() {
		if(inited) return;
		fact.assign(modulo, 1);
		invfact.assign(modulo, 1);
		for(ll i = 1; i < modulo; ++i) {
			fact[i] = ll(fact[i - 1]) * i % modulo;
		}
		invfact[modulo - 1] = qpow<modulo>(fact[modulo - 1], modulo - 2);
		for(ll i = modulo - 2; i >= 0; --i) {
			invfact[i] = ll(invfact[i + 1]) * (i + 1) % modulo;
		}
		inited = true;
	}
};
