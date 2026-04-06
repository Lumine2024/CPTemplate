#pragma once
#include "math/comb.h"

template<ll modulo, ll maxn = 500005> struct Catalan {
	Catalan() = delete;
	static int get(int n) {
		ensure_init();
		return cat[n];
	}

private:
	static inline int cat[maxn];
	static void ensure_init() {
		static bool inited = false;
		if(inited) return;
		cat[0] = 1;
		for(int i = 1; i < maxn; ++i) {
			cat[i] = (Comb<modulo>::binom(2 * i, i) -
					  Comb<modulo>::binom(2 * i, i - 1) + modulo) %
					 modulo;
		}
		inited = true;
	}
};
