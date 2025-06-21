#pragma once
#include <bits/stdc++.h>
#include "Maths/ModInt.hpp"
using namespace std;
using ll = long long;
using ull = unsigned long long;

namespace _sterling {
constexpr ll maxn = 5005;
}
ll sterling[_sterling::maxn][_sterling::maxn];
int init_sterling = [] {
	sterling[0][0] = 1;
	for(int i = 1; i < _sterling::maxn; ++i) {
		sterling[i][0] = 0;
		for(int j = 1; j <= i; ++j) {
			sterling[i][j] = (sterling[i - 1][j - 1] + sterling[i - 1][j] * j) % modulo;
		}
	}
	return 0;
}();