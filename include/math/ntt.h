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
	auto ntt = [](auto &&ntt, vector<Z> &f, bool inv) -> void {
		int n = f.size();
		if(n == 1) return;
		vector<Z> f0(n / 2), f1(n / 2);
		for(int i = 0; i < n / 2; ++i) {
			f0[i] = f[2 * i];
			f1[i] = f[2 * i + 1];
		}
		ntt(ntt, f0, inv);
		ntt(ntt, f1, inv);
		Z w = 1, wn = qpow<X>(g<X>, (X - 1) / n);
		if(inv) wn = Z(1) / wn;
		for(int t = 0; t < n / 2; ++t) {
			Z u = f0[t], v = w * f1[t];
			f[t] = u + v;
			f[t + n / 2] = u - v;
			w *= wn;
		}
	};
	ntt(ntt, ca, false);
	ntt(ntt, cb, false);
	for(int i = 0; i < n; ++i) ca[i] *= cb[i];
	ntt(ntt, ca, true);
	for(int i = 0; i < n; ++i) ca[i] /= n;
	while(ca.size() > (a.size() + b.size() - 1)) ca.pop_back();
	return ca;
}
