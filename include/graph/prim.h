#pragma once
#include "graph/edge.h"

template<WeightedEdgeT Edge>
ll prim(const vector<vector<Edge>> &g) {
	int n = g.size();
	vector<bool> vis(n, false);
	vector<ll> d(n, inf);
	d[0] = 0;
	priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
	pq.emplace(0, 0);
	ll ret = 0;
	while(!pq.empty()) {
		auto [w, v] = pq.top();
		pq.pop();
		if(vis[v]) continue;
		vis[v] = true;
		ret += w;
		for(auto &e : g[v]) {
			if(!vis[e.v] && d[e.v] > e.w) {
				d[e.v] = e.w;
				pq.emplace(e.w, e.v);
			}
		}
	}
	for(bool b : vis) {
		if(!b) return inf;
	}
	return ret;
}
