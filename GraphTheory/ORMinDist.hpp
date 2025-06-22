#pragma once
#include <bits/stdc++.h>
#include "DataStructures/DSU.hpp"
using namespace std;
using ll = long long;
using ull = unsigned long long;

int or_mindist(vector<tuple<int, int, int>> &edges, int n) {
	int ans = (1 << 30) - 1;
	for(int i = 29; i >= 0; i--) {
		ans ^= (1 << i);
		DSU dsu(n);
		for(auto &[u, v, w] : edges) {
			if((w & ans) == w) {
				dsu.connect(u, v);
			}
		}
		if(!dsu.is_connected(0, n - 1)) {
			ans ^= (1 << i);
		}
	}
	return ans;
}