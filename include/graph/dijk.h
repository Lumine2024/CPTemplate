#pragma once
#include "edge.h"

template<WeightedEdgeT Edge>
vector<ll> dijkstra(const vector<vector<Edge>> &graph, int s) {
	int n = graph.size();
	vector<ll> di(n, inf);
	di[s] = 0;
	vector<bool> vis(n, false);
	priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
	pq.emplace(0, s);
	while(!pq.empty()) {
		auto [_, u] = pq.top();
		pq.pop();
		if(vis[u]) continue;
		vis[u] = true;
		for(auto &e : graph[u]) {
			if(!vis[e.v] && di[e.v] > di[u] + e.w) {
				di[e.v] = di[u] + e.w;
				pq.emplace(di[e.v], e.v);
			}
		}
	}
	return di;
}
