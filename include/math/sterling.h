#pragma once
#include "common.h"

template<ll maxn, ll modulo> struct Sterling {
	Sterling() = delete;
	static int get(ll n, ll k) {
		ensure_init();
		if(n < 0 || k < 0 || k > n || n >= maxn) return 0;
		return ster[n][k];
	}

private:
	// static constexpr int maxn = 5005;
	static inline int ster[maxn][maxn];
	static void ensure_init() {
		static bool inited = false;
		if(inited) return;
		ster[0][0] = 1;
		for(ll i = 1; i < maxn; ++i) {
			ster[i][0] = 0;
			for(ll j = 1; j < i; ++j) {
				ster[i][j] =
					(ll(ster[i - 1][j - 1]) + ll(ster[i - 1][j]) * j) % modulo;
			}
			ster[i][i] = 1;
		}
		inited = true;
	}
};
