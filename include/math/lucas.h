#pragma once
#include "common.h"

template<ll modulo>
struct Lucas {
	Lucas() = delete;
	static ll binom(ll n, ll m) {
		init();
		if(m < 0 || m > n) return 0;
		if(m == 0) return 1;
		auto small = [&](int n, int m) {
			if(m < 0 || m > n) return 0ll;
			return ll(fact[n]) * ll(invfact[m]) % modulo * ll(invfact[n - m]) %
				   modulo;
		};
		return binom(n / modulo, m / modulo) * small(n % modulo, m % modulo) %
			   modulo;
	}

private:
	static inline int fact[modulo], invfact[modulo];
	static inline bool inited = false;
	static void init() {
		if(inited) return;
		inited = true;
		fact[0] = 1;
		for(ll i = 1; i < modulo; ++i) {
			fact[i] = ll(fact[i - 1]) * i % modulo;
		}
		invfact[modulo - 1] = modulo - 1;
		for(ll i = modulo - 2; i >= 0; --i) {
			invfact[i] = ll(invfact[i + 1]) * (i + 1) % modulo;
		}
	}
};
