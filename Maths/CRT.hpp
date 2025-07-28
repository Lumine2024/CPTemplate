#pragma once
#include <bits/stdc++.h>
#include "Maths/EXGCD.hpp"
using namespace std;
using ll = long long;
using ull = unsigned long long;

// @returns (a, b) so that answer is a + kb, k\in N_+
pair<ll, ll> crt(const vector<ll> &rem, const vector<ll> &mod) {
	int n = rem.size();
	ll modulo_ = 1, ans = 0;
	for(int i = 0; i < n; ++i) {
		modulo_ *= mod[i];
	}
	for(int i = 0; i < n; ++i) {
		ll m = modulo_ / mod[i];
		auto [_, b, __] = exgcd(m, mod[i]);
		ans = (ans + ((rem[i] * m) % modulo_ * b) % modulo_) % modulo_;
	}
	return pair((ans % modulo_ + modulo_) % modulo_, modulo_);
}

pair<ll, ll> excrt(const vector<ll> &rem, const vector<ll> &mod) {
	int n = rem.size();
	ll r1 = rem[0], m1 = mod[0];
	for(int i = 1; i < n; ++i) {
		ll r2 = rem[i], m2 = mod[i];
		auto [g, p, _] = exgcd(m1, m2);
		if((r2 - r1) % g != 0) {
			return { -1, -1 };
		}
		ll v = m2 / g, x = (r2 - r1) / g;
		ll u = p % v * x % v;
		ll w = (u % v + v) % v;
		r1 += w * m1;
		m1 = lcm(m1, m2);
	}
	return { (r1 % m1 + m1) % m1, m1 };
}