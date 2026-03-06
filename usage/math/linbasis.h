#pragma once
#include "common.h"

constexpr ll modulo = 998244353;
inline ll qpow(ll x, ll n) {
	ll ret = 1;
	for(; n; n >>= 1, x = x * x % modulo)
		if(n & 1) ret = ret * x % modulo;
	return ret;
}

struct LinearBasis_XOR {
	LinearBasis_XOR() : base(61) {}
	void insert(ll val) {
		for(int i = 60; i >= 0; --i) {
			if(((val >> i) & 1) == 0) continue;
			if(base[i] == 0) {
				base[i] = val;
				return;
			}
			val ^= base[i];
		}
	}
	ll query_max() const {
		ll ans = 0;
		for(int i = 60; i >= 0; --i) {
			if((ans ^ base[i]) > ans) {
				ans ^= base[i];
			}
		}
		return ans;
	}

private:
	vector<ll> base;
};
