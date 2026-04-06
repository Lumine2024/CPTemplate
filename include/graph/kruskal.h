#pragma once
#include "ds/dsu.h"

constexpr ll inf = 0x3f3f3f3f3f3f3f3f;

struct Edge {
	int u, v;
	ll w;
};

ll kruskal(vector<Edge> &edges, int n) {
	DSU dsu(n);
	ll ans = 0;
	sort(edges.begin(), edges.end(),
		 [](const Edge &a, const Edge &b) { return a.w < b.w; });
	for(auto &e : edges) {
		if(!dsu.is_connected(e.u, e.v)) {
			dsu.connect(e.u, e.v);
			ans += e.w;
		}
	}
	for(int i = 1; i < n; ++i) {
		if(!dsu.is_connected(i, 0)) return inf;
	}
	return ans;
}
