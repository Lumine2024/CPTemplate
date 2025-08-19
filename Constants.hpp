#pragma once
#include <bits/stdc++.h>

// Common type aliases
using ll = long long;
using ull = unsigned long long;
using ld = long double;

// Standard library namespace
using namespace std;

// General constants
constexpr ll modulo = 998244353, g = 3;
constexpr ll maxn = 100005;

// Infinity constants for different types
constexpr int inf_int = 0x3f3f3f3f;
constexpr ll inf = 0x3f3f3f3f3f3f3f3f;

// Mathematical constants
constexpr double pi = 3.14159265358979323846264338327950288;

// Common mathematical functions
inline ll qpow(ll x, ll n) {
	ll ret = 1;
	for(; n != 0; n >>= 1, x = x * x % modulo) {
		if(n & 1) ret = ret * x % modulo;
	}
	return ret;
}

// Domain-specific constants
namespace Geometry {
    using ld = long double;
    constexpr ld eps = 1e-9;
    constexpr ld pi = 3.1415926535897932384626l;
    constexpr ld inf = 1e12l;
}