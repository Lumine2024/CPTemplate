#pragma once
#include <bits/stdc++.h>
#include "DataStructures/DSU.hpp"
using namespace std;
using ll = long long;
using ull = unsigned long long;
namespace _kruskal {
constexpr ll inf = 0x3f3f3f3f3f3f3f3f;
}
struct Edge {
	int u, v;
	ll w;
};
// 拿个并查集板子下来谢谢喵
ll kruskal(vector<Edge> &edges, int n) {
	DSU dsu(n);
	ll ans = 0;
	sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) {
		return a.w < b.w;
	});
	for(auto &e : edges) {
		if(!dsu.is_connected(e.u, e.v)) {
			dsu.connect(e.u, e.v);
			ans += e.w;
		}
	}
	for(int i = 1; i < n; ++i) {
		if(!dsu.is_connected(i, 0)) {
			return _kruskal::inf;
		}
	}
	return ans;
}