#pragma once
#include "graph/edge.h"

// 返回空vector说明有负环
template<WeightedEdgeT Edge>
vector<ll> spfa(const vector<vector<Edge>> &g, int s) {
	int n = g.size();
	vector<ll> d(n, inf);
	vector<int> cnt(n, 0);
	vector<bool> inq(n, false);
	queue<int> q;
	q.push(s);
	d[s] = 0;
	inq[s] = true;
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		inq[u] = false;
		for(auto &e : g[u]) {
			if(d[e.v] > d[u] + e.w) {
				d[e.v] = d[u] + e.w;
				if(!inq[e.v]) {
					inq[e.v] = true;
					q.push(e.v);
					cnt[e.v] = cnt[u] + 1;
					if(cnt[e.v] > n) return {};
				}
			}
		}
	}
	return d;
}
