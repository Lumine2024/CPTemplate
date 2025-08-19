#pragma once
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;

constexpr ll modulo = 998244353, g = 3;
constexpr ll maxn = 100005;
constexpr int inf_int = 0x3f3f3f3f;
constexpr ll inf = 0x3f3f3f3f3f3f3f3f;
constexpr double pi = 3.14159265358979323846264338327950288;

inline ll qpow(ll x, ll n) {
	ll ret = 1;
	for(; n != 0; n >>= 1, x = x * x % modulo) {
		if(n & 1) ret = ret * x % modulo;
	}
	return ret;
}
template<class T> bool chkmin(T &x, const T &y) {
	if(x > y) {
		x = y;
		return true;
	}
	return false;
}

namespace geo {
    using ld = long double;
    constexpr ld eps = 1e-9;
    constexpr ld pi = 3.14159265358979323846264338327950288l;
    constexpr ld inf = 1e12l;
}