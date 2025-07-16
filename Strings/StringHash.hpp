#pragma once
#include <bits/stdc++.h>
#include "Constants.hpp"
using namespace std;
using ll = long long;
using ull = unsigned long long;

const ull c = (ull)chrono::steady_clock::now().time_since_epoch().count();
const ull mul1 = c % 131 + 131, mul2 = c % 13331 + 13331;
ull pmul1[maxn], pmul2[maxn];
int init_stringhash = [] {
	pmul1[0] = pmul2[0] = 1;
	for(int i = 1; i < maxn; ++i) {
		pmul1[i] = pmul1[i - 1] * mul1 % modulo;
		pmul2[i] = pmul2[i - 1] * mul2;
	}
	return 0;
}();

struct StringHash {
	StringHash(const string &s) : p1(s.size() + 1, 0), p2(s.size() + 1, 0) {
		for(int i = 0; i < s.size(); ++i) {
			p1[i + 1] = (p1[i] * mul1 + s[i]) % modulo;
			p2[i + 1] = p2[i] * mul2 + s[i];
		}
	}
	ull substr(int l, int r) const {
		ull ret1 = (p1[r] - p1[l] * pmul1[r - l] % modulo + modulo) % modulo;
		ull ret2 = p2[r] - p2[l] * pmul2[r - l];
		return (ret1 << 3) ^ (ret1 >> 5) ^ ret2;
	}
private:
	vector<ull> p1, p2;
};