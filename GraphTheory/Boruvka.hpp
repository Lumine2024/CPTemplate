#pragma once
#include <bits/stdc++.h>
#include "DataStructures/DSU.hpp"
using namespace std;
using ll = long long;
using ull = unsigned long long;
namespace _boruvka {
constexpr ll inf = 0x3f3f3f3f3f3f3f3f;
}
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
			mst[i] = Edge(-1, -1, _boruvka::inf);
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
			if(w == _boruvka::inf) return _boruvka::inf;
			if(!dsu.is_connected(u, v)) {
				dsu.connect(u, v);
				ans += w;
				--c;
				flag = true;
			}
		}
		if(!flag) {
			return _boruvka::inf;
		}
	}
	return ans;
}