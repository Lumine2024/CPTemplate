#pragma once
#include "ds/dsu.h"

constexpr ll inf = 0x3f3f3f3f3f3f3f3f;

struct Edge {
	int u, v;
	ll w;
};

ll boruvka(const vector<Edge> &es, int n) {
	int m = es.size();
	DSU dsu(n);
	ll ans = 0;
	int c = n;
	vector<int> mst(n);
	while(c > 1) {
		for(int i = 0; i < n; ++i) {
			if(dsu.find(i) == i) mst[i] = -1;
		}
		for(int i = 0; i < m; ++i) {
			auto [u, v, w] = es[i];
			int fu = dsu.find(u), fv = dsu.find(v);
			if(fu == fv) continue;
			if(mst[fu] == -1 || es[mst[fu]].w > w) mst[fu] = i;
			if(mst[fv] == -1 || es[mst[fv]].w > w) mst[fv] = i;
		}
		bool flag = false;
		for(int i = 0; i < n; ++i) {
			if(dsu.find(i) != i || mst[i] == -1) continue;
			auto [u, v, w] = es[mst[i]];
			if(!dsu.is_connected(u, v)) {
				dsu.connect(u, v);
				ans += w;
				--c;
				flag = true;
			}
		}
		if(!flag) return inf;
	}
	return ans;
}
