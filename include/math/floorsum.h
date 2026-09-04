#pragma once
#include "common.h"

ll floor_sum(ll n, ll m, ll a, ll b) {
	ll ret = 0;
	while(true) {
		if(a >= m) {
			auto [d, r] = div(a, m);
			ret += n * (n - 1) / 2 * d;
			a = r;
		}
		if(b >= m) {
			auto [d, r] = div(b, m);
			ret += n * d;
			b = r;
		}
		ll ym = a * n + b;
		if(ym < m) break;
		n = ym / m;
		b = ym % m;
		swap(m, a);
	}
	return ret;
}
