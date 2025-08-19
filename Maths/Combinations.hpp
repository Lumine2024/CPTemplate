#pragma once
#include "Constants.hpp"
#include "Maths/ModInt.hpp"

struct Comb {
	Comb() = delete;
	static ll fact(ll n) {
		return _fact[n];
	}
	static ll invfact(ll n) {
		return _invfact[n];
	}
	static ll comb(ll n, ll m) {
		if(m < 0 || m > n) return 0;
		return (((ll(_fact[n]) * ll(_invfact[m])) % modulo) * ll(_invfact[n - m])) % modulo;
	}
private:
	static constexpr int _maxn = 500005;
	static inline int _fact[_maxn], _invfact[_maxn];
	static inline int init = [] {
		_fact[0] = 1;
		for(ll i = 1; i < _maxn; ++i) {
			_fact[i] = (ll(_fact[i - 1]) * i) % modulo;
		}
		_invfact[_maxn - 1] = qpow(_fact[_maxn - 1], modulo - 2);
		for(ll i = _maxn - 2; i >= 0; --i) {
			_invfact[i] = (ll(_invfact[i + 1]) * (i + 1)) % modulo;
		}
		return 0;
	}();
};