#pragma once
#include <bits/stdc++.h>
#include "Constants.hpp"
#include "Maths/ModInt.hpp"
using namespace std;
using ll = long long;
using ull = unsigned long long;

// 不预处理，一次性算一排
vector<ll> comb(ll n) {
	vector<ModInt> ret_(n + 1);
	ret_[0] = ret_[n] = 1;
	for(int i = 1, j = n - 1; i < j; ++i, --j) {
		ret_[i] = ret_[j] = ret_[i - 1] * ModInt(n - i + 1) / ModInt(i);
	}
	vector<ll> ret(ret_.begin(), ret_.end());
	return ret;
}

ll qpow(ll x, ll n);
ll fact[maxn], invfact[maxn];
static int init_combinations = [] {
	fact[0] = 1;
	for(int i = 1; i < maxn; ++i) {
		fact[i] = (fact[i - 1] * i) % modulo;
	}
	invfact[maxn - 1] = qpow(fact[maxn - 1], modulo - 2);
	for(int i = maxn - 2; i >= 0; --i) {
		invfact[i] = (invfact[i + 1] * (i + 1)) % modulo;
	}
	return 0;
}();
ll comb(ll n, ll m) {
	if(m < 0 || m > n) return 0;
	return (((fact[n] * invfact[m]) % modulo) * invfact[n - m]) % modulo;
}