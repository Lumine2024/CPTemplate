#pragma once
#include <bits/stdc++.h>
#include "Constants.hpp"
using namespace std;
using ll = long long;
using ull = unsigned long long;

ll prim(const vector<vector<pair<int, ll>>> &graph) {
	int n = graph.size();
	vector<bool> visited(n, false);
	vector<ll> dist(n, inf);
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
			return inf;
		}
	}
	return ret;
}