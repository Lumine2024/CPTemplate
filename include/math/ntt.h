#pragma once
#include "math/modint.h"

template<unsigned X>
constexpr unsigned g = 0;
template<>
constexpr unsigned g<998244353> = 3;
template<>
constexpr unsigned g<469762049> = 3;
template<>
constexpr unsigned g<167772161> = 3;
template<>
constexpr unsigned g<104857601> = 3;

template<unsigned X>
	requires(g<X> != 0)
vector<ModInt<X>> multiply(const vector<ModInt<X>> &a,
						   const vector<ModInt<X>> &b) {
	using Z = ModInt<X>;
	int n = bit_ceil(a.size() + b.size());
	vector<Z> ca(n), cb(n);
	for(int i = 0; i < a.size(); ++i) ca[i] = a[i];
	for(int i = 0; i < b.size(); ++i) cb[i] = b[i];
	auto ntt = [](vector<Z> &f, bool inv) -> void {
		int n = f.size();
		for(int i = 1, j = 0; i < n; ++i) {
			int bit = n >> 1;
			for(; (j & bit) != 0; bit >>= 1) j ^= bit;
			j ^= bit;
			if(i < j) swap(f[i], f[j]);
		}
		for(int len = 2; len <= n; len *= 2) {
			Z wn = Z(qpow<X>(g<X>, (X - 1) / len));
			if(inv) wn = Z(1) / wn;
			for(int i = 0; i < n; i += len) {
				Z w = 1;
				for(int j = 0; j < len / 2; ++j) {
					Z u = f[i + j], v = f[i + j + len / 2] * w;
					f[i + j] = u + v;
					f[i + j + len / 2] = u - v;
					w *= wn;
				}
			}
		}
	};
	ntt(ca, false);
	ntt(cb, false);
	for(int i = 0; i < n; ++i) ca[i] *= cb[i];
	ntt(ca, true);
	Z in = Z(1) / Z(n);
	for(int i = 0; i < n; ++i) ca[i] *= in;
	while(ca.size() > (a.size() + b.size() - 1)) ca.pop_back();
	return ca;
}
