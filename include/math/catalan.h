#pragma once
#include "comb.h"

template<ll modulo> struct Catalan {
	Catalan() = delete;
	static ll get(int x) {
		return _cat[x];
	}

private:
	static constexpr int _maxn = 250005;
	static inline int _cat[_maxn];
	static inline int init = [] {
		_cat[0] = 1;
		for(int i = 1; i < _maxn; ++i) {
			_cat[i] = (Comb<modulo>::binom(2 * i, i) -
					   Comb<modulo>::binom(2 * i, i - 1) + modulo) %
					  modulo;
		}
		return 0;
	}();
};
