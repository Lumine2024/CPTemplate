#pragma once
#include "common.h"

template<ll maxn, ll modulo> struct Sterling {
	Sterling() = delete;
	static inline int ster[maxn][maxn];

private:
	// static constexpr int maxn = 5005;
	static inline int init = [] {
		ster[0][0] = 1;
		for(ll i = 1; i < maxn; ++i) {
			ster[i][0] = 0;
			for(ll j = 1; j < i; ++j) {
				ster[i][j] =
					(ll(ster[i - 1][j - 1]) + ll(ster[i - 1][j]) * j) % modulo;
			}
		}
		return 0;
	}();
};
