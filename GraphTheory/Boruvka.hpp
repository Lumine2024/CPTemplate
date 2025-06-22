#pragma once
#include <bits/stdc++.h>
#include "DataStructures/DSU.hpp"
#include "Constants.hpp"
using namespace std;
using ll = long long;
using ull = unsigned long long;
struct Edge {
	int u, v;
	ll w;
};
ll boruvka(const vector<Edge> &edges, int n) {
	DSU dsu(n);
	ll ans = 0;
	int c = n;
	vector<Edge> mst(n);
	while(c > 1) {
		for(int i = 0; i < n; ++i) {
			if(dsu.find(i) != i) continue;
			mst[i] = Edge(-1, -1, inf);
		}
		for(auto [u, v, w] : edges) {
			int fu = dsu.find(u), fv = dsu.find(v);
			if(fu == fv) continue;
			if(mst[fu].w > w) {
				mst[fu] = Edge(u, v, w);
			}
			if(mst[fv].w > w) {
				mst[fv] = Edge(u, v, w);
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