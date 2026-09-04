#pragma once
#include "common.h"

struct LinearBasis {
	LinearBasis() : base{} {}
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
	ll max_xor() const {
		ll ans = 0;
		for(int i = 60; i >= 0; --i) {
			if((ans ^ base[i]) > ans) {
				ans ^= base[i];
			}
		}
		return ans;
	}
	ll min_xor() const {
		for(int i = 0; i <= 60; ++i) {
			if(base[i] != 0) {
				return base[i];
			}
		}
		return 0;
	}
	ll kth_xor(ll k) const {
		// placeholder
		return 0;
	}
	bool can_repr(ll dest) const {
		for(int i = 60; i >= 0; --i) {
			if((dest >> i) & 1) {
				dest ^= base[i];
			}
		}
		return dest == 0;
	}

private:
	array<ll, 64> base;
};
