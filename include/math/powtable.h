#pragma once
#include "math/basic.h"

template<class T>
concept CanInv = requires(T x) {
	{ x.inv() } -> convertible_to<T>;
};

template<class T, bool can_inv = CanInv<T>>
struct PowTable {
	PowTable() = default;
	explicit PowTable(T x) {
		p[0] = x;
		for(int i = 1; i < 64; ++i) {
			p[i] = p[i - 1] * p[i - 1];
		}
	}
	T qpow(T x, ll n, T one) const {
		for(int i = 0; n > 0; i++, n >>= 1)
			if((n & 1) == 1) one = one * p[i];
		return one;
	}

private:
	array<T, 64> p;
};

template<class T>
struct PowTable<T, true> {
	PowTable() = default;
	explicit PowTable(T x) {
		p[0] = x;
		ip[0] = x.inv();
		for(int i = 1; i < 64; ++i) {
			p[i] = p[i - 1] * p[i - 1];
			ip[i] = ip[i - 1] * ip[i - 1];
		}
	}
	T qpow(T x, ll n, T one) const {
		const auto &t = n >= 0 ? p : ip;
		n = abs(n);
		for(int i = 0; n > 0; i++, n >>= 1)
			if((n & 1) == 1) one = one * t[i];
		return one;
	}

private:
	array<T, 64> p, ip;
};