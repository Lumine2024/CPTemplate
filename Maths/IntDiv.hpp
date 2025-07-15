#pragma once
#include <bits/stdc++.h>
#include "Constants.hpp"
using namespace std;
using ll = long long;
using ull = unsigned long long;

// 要计算\sum floor(n/i)
ll intdiv(ll n) {
    ll ans = 0;
	for(ll b = 1; b <= n;) {
		ll val = n / b;
		ll r = n / val;
		ll len = r - b + 1;
		ans = (ans + (len % modulo * val % modulo)) % modulo;
		b = r + 1;
	}
    return ans;
}