#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

constexpr ll modulo = 9'9824'4353, maxn = 50005;
ll qpow(ll x, ll n) {
	ll ret = 1;
	while(n) {
		if(n & 1) ret = ret * x % modulo;
		x = x * x % modulo;
		n >>= 1;
	}
	return ret;
}
struct ModInt {
	ModInt(ll v = 0) : val(v % modulo) {}
	ModInt operator+(const ModInt &rhs) const {
		return ModInt((val + rhs.val) % modulo);
	}
	ModInt operator-(const ModInt &rhs) const {
		return ModInt((val - rhs.val + modulo) % modulo);
	}
	ModInt operator*(const ModInt &rhs) const {
		return ModInt((val * rhs.val) % modulo);
	}
	ModInt operator/(const ModInt &rhs) const {
		return ModInt(val * qpow(rhs.val, modulo - 2) % modulo);
	}
	ModInt power(int N) const {
		ModInt ret = 1;
		ModInt base = val;
		while(N) {
			if(N & 1) ret = ret * base;
			base = base * base;
			N >>= 1;
		}
		return ret;
	}
	operator ll &() {
		return val;
	}
private:
	ll val;
};
// 底数相同时的快速幂，预处理O(sqrtn)，查询O(1)
ll power2[maxn], power2m[maxn];
int init_power2 = [] {
	power2[0] = power2m[0] = 1;
	for(int i = 1; i < maxn; ++i) {
		power2[i] = (power2[i - 1] * 2) % modulo;
	}
	power2m[1] = (power2[maxn - 1] * 2) % modulo;
	for(int i = 2; i < maxn; ++i) {
		power2m[i] = (power2m[i - 1] * power2m[1]) % modulo;
	}
	return 0;
}();
ll pow2(ll x) {
	ll i = x / maxn, j = x % maxn;
	return (power2m[i] * power2[j]) % modulo;
}