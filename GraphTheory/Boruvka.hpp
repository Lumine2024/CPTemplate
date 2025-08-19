#pragma once
#include "DataStructures/DSU.hpp"
#include "Constants.hpp"

namespace BoruvkaAlgorithm {
    struct Edge {
        int u, v;
        ll w;
    };
}
ll boruvka(const vector<BoruvkaAlgorithm::Edge> &edges, int n) {
	DSU dsu(n);
	ll ans = 0;
	int c = n;
	vector<BoruvkaAlgorithm::Edge> mst(n);
	while(c > 1) {
		for(int i = 0; i < n; ++i) {
			if(dsu.find(i) != i) continue;
			mst[i] = BoruvkaAlgorithm::Edge{-1, -1, inf};
		}
		for(auto [u, v, w] : edges) {
			int fu = dsu.find(u), fv = dsu.find(v);
			if(fu == fv) continue;
			if(mst[fu].w > w) {
				mst[fu] = BoruvkaAlgorithm::Edge{u, v, w};
			}
			if(mst[fv].w > w) {
				mst[fv] = BoruvkaAlgorithm::Edge{u, v, w};
			}
		}
		bool flag = false;
		for(int i = 0; i < n; ++i) {
			if(dsu.find(i) != i) continue;
			auto [u, v, w] = mst[i];
			if(w == inf) return inf;
			if(!dsu.is_connected(u, v)) {
				dsu.connect(u, v);
				ans += w;
				--c;
				flag = true;
			}
		}
		if(!flag) {
			return inf;
		}
	}
	return ans;
}