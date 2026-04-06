#pragma once
#include "graph/edge.h"

// 返回空vector说明有负环
template<WeightedEdgeT Edge>
vector<ll> spfa(const vector<vector<Edge>> &graph, int start) {
	int n = graph.size();
	vector<ll> dist(n, inf);
	vector<int> cnt(n, 0);
	vector<bool> inq(n, false);
	queue<int> q;
	q.push(start);
	dist[start] = 0;
	inq[start] = true;
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		inq[u] = false;
		for(auto &e : graph[u]) {
			if(dist[e.v] > dist[u] + e.w) {
				dist[e.v] = dist[u] + e.w;
				if(!inq[e.v]) {
					inq[e.v] = true;
					q.push(e.v);
					cnt[e.v] = cnt[u] + 1;
					if(cnt[e.v] > n) return {};
				}
			}
		}
	}
	return dist;
}
