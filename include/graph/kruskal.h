#pragma once
#include "ds/dsu.h"

constexpr ll inf = 0x3f3f3f3f3f3f3f3f;

struct Edge {
	int u, v;
	ll w;
};

ll kruskal(vector<Edge> &es, int n) {
	DSU d(n);
	ll ans = 0;
	sort(es.begin(), es.end(),
		 [](const Edge &a, const Edge &b) { return a.w < b.w; });
	for(auto &e : es) {
		if(!d.is_connected(e.u, e.v)) {
			d.connect(e.u, e.v);
			ans += e.w;
		}
	}
	for(int i = 1; i < n; ++i) {
		if(!d.is_connected(i, 0)) return inf;
	}
	return ans;
}
