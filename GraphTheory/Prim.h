#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

namespace _prim {
constexpr ll inf = 0x3f3f3f3f3f3f3f3f;
}
ll prim(const vector<vector<pair<int, ll>>> &graph) {
	int n = graph.size();
	vector<bool> visited(n, false);
	vector<ll> dist(n, _prim::inf);
	dist[0] = 0;
	priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
	pq.emplace(0, 0);
	ll ret = 0;
	while(!pq.empty()) {
		auto [w, v] = pq.top();
		pq.pop();
		if(visited[v]) continue;
		visited[v] = true;
		ret += w;
		for(auto [u, w] : graph[v]) {
			if(!visited[u] && dist[u] > w) {
				dist[u] = w;
				pq.emplace(w, u);
			}
		}
	}
	for(bool b : visited) {
		if(!b) {
			return _prim::inf;
		}
	}
	return ret;
}