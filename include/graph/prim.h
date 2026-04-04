#pragma once
#include "edge.h"

template<WeightedEdgeT Edge> ll prim(const vector<vector<Edge>> &graph) {
	int n = graph.size();
	vector<bool> vis(n, false);
	vector<ll> dist(n, inf);
	dist[0] = 0;
	priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
	pq.emplace(0, 0);
	ll ret = 0;
	while(!pq.empty()) {
		auto [w, v] = pq.top();
		pq.pop();
		if(vis[v]) continue;
		vis[v] = true;
		ret += w;
		for(auto &e : graph[v]) {
			if(!vis[e.v] && dist[e.v] > e.w) {
				dist[e.v] = e.w;
				pq.emplace(e.w, e.v);
			}
		}
	}
	for(bool b : vis) {
		if(!b) return inf;
	}
	return ret;
}
