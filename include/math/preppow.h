#pragma once
#include "common.h"

template<ll modulo>
struct PreprocessedPow {
	PreprocessedPow(ll k, ll maxn) {
		k = norm<modulo>(k);
		m = ceil(sqrt(maxn + 1.5));
		powerk.assign(m, 1);
		powerkm.assign(m, 1);
		for(int i = 1; i < m; ++i) {
			powerk[i] = ll(powerk[i - 1]) * k % modulo;
		}
		powerkm[1] = ll(powerk[m - 1]) * k % modulo;
		for(int i = 2; i < m; ++i) {
			powerkm[i] = ll(powerkm[i - 1]) * ll(powerkm[1]) % modulo;
		}
	}
	ll pow(ll n) const {
		ll i = n / m, j = n % m;
		return ll(powerkm[i]) * ll(powerk[j]) % modulo;
	}
	ll operator()(ll n) const {
		return pow(n);
	}
	ll operator[](ll n) const {
		return pow(n);
	}

private:
	int m;
	vector<int> powerk, powerkm;
};
