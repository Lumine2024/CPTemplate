#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

struct MyHash {
	size_t operator()(ll x) const noexcept {
		x ^= (x >> 21);
		x ^= (x << 37);
		x ^= (x >> 4);
		x *= 0x27d4eb2f165667c5;
		x ^= (x >> 28);
		x *= 0x165667b19e3779f9;
		x ^= (x >> 31);
		return x ^ c;
	}
private:
	static inline size_t c = (size_t)chrono::steady_clock::now().time_since_epoch().count();
};