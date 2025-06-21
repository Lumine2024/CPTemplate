#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

namespace _ntt {
constexpr ll modulo = 9'9824'4353, g = 3;
// constexpr ll modulo = 10'0000'0007, g = 5; 不可以
}
ll qpow(ll x, ll n) {
	ll ret = 1;
	while(n) {
		if(n & 1) {
			ret = ret * x % _ntt::modulo;
		}
		x = x * x % _ntt::modulo;
		n >>= 1;
	}
	return ret;
}
vector<ll> multiply(const vector<ll> &a, const vector<ll> &b) {
	int n = 1;
	while(n < a.size() + b.size()) {
		n <<= 1;
	}
	vector<ll> ca(n), cb(n);
	for(int i = 0; i < a.size(); ++i) {
		ca[i] = a[i];
	}
	for(int i = 0; i < b.size(); ++i) {
		cb[i] = b[i];
	}
	auto ntt = [](auto &&ntt, vector<ll> &f, bool invert) -> void {
		int n = f.size();
		if(n == 1) return;
		vector<ll> f0(n / 2), f1(n / 2);
		for(int i = 0; i < n / 2; ++i) {
			f0[i] = f[2 * i];
			f1[i] = f[2 * i + 1];
		}
		ntt(ntt, f0, invert);
		ntt(ntt, f1, invert);
		ll w = 1, wn = qpow(_ntt::g, (_ntt::modulo - 1) / n);
		if(invert) {
			wn = qpow(wn, _ntt::modulo - 2);
		}
		for(int t = 0; t < n / 2; ++t) {
			ll u = f0[t], v = w * f1[t] % _ntt::modulo;
			f[t] = (u + v) % _ntt::modulo;
			f[t + n / 2] = (u - v + _ntt::modulo) % _ntt::modulo;
			w = w * wn % _ntt::modulo;
		}
	};
	ntt(ntt, ca, false);
	ntt(ntt, cb, false);
	for(int i = 0; i < n; ++i) {
		ca[i] = ca[i] * cb[i] % _ntt::modulo;
	}
	ntt(ntt, ca, true);
	for(int i = 0; i < n; ++i) {
		ca[i] = ca[i] * qpow(n, _ntt::modulo - 2) % _ntt::modulo;
	}
	while(ca.size() > (a.size() + b.size() - 1)) {
		ca.pop_back();
	}
	return ca;
}