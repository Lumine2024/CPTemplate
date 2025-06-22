#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

// @returns (gcd, x, y) so that gcd = ax + by
tuple<ll, ll, ll> exgcd(ll a, ll b) {
	if(b == 0) return tuple(a, 1, 0);
	auto [g, x, y] = exgcd(b, a % b);
	return tuple(g, y, x - (a / b) * y);
}