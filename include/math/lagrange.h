#pragma once
#include "preppow.h"
#include "comb.h"

template<ll modulo>
ll lagrange(const vector<ll> &x, const vector<ll> &y, ll x0) {
	int n = x.size();
	vector<ll> iden(n);
	for(int i = 0; i < n; ++i) {
		ll den = 1;
		for(int j = 0; j < n; ++j) {
			if(i != j) den = den * (x[i] - x[j] + modulo) % modulo;
		}
		iden[i] = qpow(den, modulo - 2);
	}
	ll ret = 0;
	for(int i = 0; i < n; ++i) {
		ll num = 1;
		for(int j = 0; j < n; ++j) {
			if(i != j) num = num * (x0 - x[j] + modulo) % modulo;
		}
		ret = (ret + y[i] * num % modulo * iden[i]) % modulo;
	}
	return ret;
}

// if x[i] = i for i = 0 to x.size() - 1, then call this to solve in O(n)
template<ll modulo> ll lagrange(const vector<ll> &y, ll x0) {
	int n = y.size();
	vector<ll> pre(n), suf(n);
	pre[0] = (x0 - 0 + modulo) % modulo;
	for(int i = 1; i < n; ++i) {
		pre[i] = pre[i - 1] * (x0 - i + modulo) % modulo;
	}
	suf[n - 1] = (x0 - (n - 1) + modulo) % modulo;
	for(int i = n - 2; i >= 0; --i) {
		suf[i] = suf[i + 1] * (x0 - i + modulo) % modulo;
	}
	ll ret = 0;
	for(int i = 0; i < n; ++i) {
		ll term = y[i];
		if(i > 0) term = term * pre[i - 1] % modulo;
		if(i < n - 1) term = term * suf[i + 1] % modulo;
		ll den = Comb<modulo>::invfact(i) * Comb<modulo>::invfact(n - 1 - i) %
				 modulo;
		if((n - 1 - i) % 2) den = modulo - den;
		ret = (ret + term * den) % modulo;
	}
	return ret;
}
