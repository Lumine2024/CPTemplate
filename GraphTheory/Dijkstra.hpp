#pragma once
#include <bits/stdc++.h>
#include "Constants.hpp"
using namespace std;
using ll = long long;
using ull = unsigned long long;
vector<ll> dijkstra(vector<vector<pair<int, ll>>> &graph, int start) noexcept {
	int v = graph.size();
	vector<ll> dist(v, inf);
	dist[start] = 0;
	vector<bool> visited(v, false);
	priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
	for(auto [vtx, w] : graph[start]) {
		dist[vtx] = w;
		pq.emplace(w, vtx);
	}
	while(!pq.empty()) {
		auto [w, vtx] = pq.top();
		pq.pop();
		if(visited[vtx]) continue;
		visited[vtx] = true;
		for(auto [vt, ww] : graph[vtx]) {
			if(!visited[vt]) {
				if(dist[vt] > dist[vtx] + ww) {
					dist[vt] = dist[vtx] + ww;
					pq.emplace(dist[vt], vt);
				}
			}
		}
	}
	return dist;
}