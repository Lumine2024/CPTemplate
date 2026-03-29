#pragma once
#include "preppow.h"

template<ll modulo> struct Comb {
	Comb() = delete;
	static void ensure_init() {
		(void)init;
	}
	static ll fact(ll n) {
		ensure_init();
		return fac[n];
	}
	static ll invfact(ll n) {
		ensure_init();
		return ifac[n];
	}
	static ll perm(ll n, ll m) {
		ensure_init();
		if(m < 0 || m > n || n < 0) return 0;
		ll fn = fac[n], inm = ifac[n - m];
		return fn * inm % modulo;
	}
	static ll binom(ll n, ll m) {
		ensure_init();
		if(m < 0 || m > n || n < 0) return 0;
		ll fn = fac[n], im = ifac[m], inm = ifac[n - m];
		return fn * im % modulo * inm % modulo;
	}

private:
	static constexpr int maxn = 500005;
	static inline int fac[maxn], ifac[maxn];
	static inline int init = [] {
		fac[0] = 1;
		for(ll i = 1; i < maxn; ++i) {
			fac[i] = (ll(fac[i - 1]) * i) % modulo;
		}
		ifac[maxn - 1] = qpow<modulo>(fac[maxn - 1], modulo - 2);
		for(ll i = maxn - 2; i >= 0; --i) {
			ifac[i] = (ll(ifac[i + 1]) * (i + 1)) % modulo;
		}
		return 0;
	}();
};
