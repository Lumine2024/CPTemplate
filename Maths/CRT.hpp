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