#pragma once
#include "math/exgcd.h"

// @returns (a, b) so that answer is a + kb, k\in N_+
template<class T>
pair<T, T> crt(const vector<T> &rem, const vector<T> &mod) {
	int n = rem.size();
	T modulo_ = 1, ans = 0;
	for(int i = 0; i < n; ++i) {
		modulo_ *= mod[i];
	}
	for(int i = 0; i < n; ++i) {
		T m = modulo_ / mod[i];
		auto [_, b, __] = exgcd<T>(m, mod[i]);
		ans = (ans + ((rem[i] * m) % modulo_ * b) % modulo_) % modulo_;
	}
	return pair((ans % modulo_ + modulo_) % modulo_, modulo_);
}

template<class T>
pair<T, T> excrt(const vector<T> &rem, const vector<T> &mod) {
	int n = rem.size();
	T r1 = rem[0], m1 = mod[0];
	for(int i = 1; i < n; ++i) {
		T r2 = rem[i], m2 = mod[i];
		auto [g, p, _] = exgcd<T>(m1, m2);
		if((r2 - r1) % g != 0) {
			return {-1, -1};
		}
		T v = m2 / g, x = (r2 - r1) / g;
		T u = p % v * x % v;
		T w = (u % v + v) % v;
		r1 += w * m1;
		m1 = lcm(m1, m2);
	}
	return {(r1 % m1 + m1) % m1, m1};
}
