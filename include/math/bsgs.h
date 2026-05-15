#pragma once
#include "others/hash.h"
#include "math/basic.h"

// returns ret so that qpow(ret, a) = b, -1 if not exist
template<ll modulo>
ll mlog(ll a, ll b) {
	if(b == 1) return 0;
	ll t = ceil(sqrt(modulo));
	ll now = b;
	unordered_map<ll, ll, MyHash> table;
	for(int i = 0; i < t; ++i) {
		table[now] = i;
		now = now * a % modulo;
	}
	ll mi = qpow<modulo>(a, t);
	now = 1;
	for(int i = 1; i <= t; ++i) {
		now = now * mi % modulo;
		if(table.contains(now)) {
			return i * t - table[now];
		}
	}
	return -1;
}
