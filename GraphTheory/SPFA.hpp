#pragma once
#include <bits/stdc++.h>
#include "Constants.hpp"
using namespace std;
using ll = long long;
using ull = unsigned long long;

// 返回空vector说明有负环
vector<ll> spfa(const vector<vector<pair<int, ll>>> &graph, int s) {
	int n = graph.size();
	vector<ll> dist(n, inf);
	vector<int> count(n, 0);
	vector<bool> inqueue(n, false);
	queue<int> q;
	q.push(s);
	dist[s] = 0;
	inqueue[s] = true;
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		inqueue[u] = false;
		for(auto [v, w] : graph[u]) {
			if(dist[v] > dist[u] + w) {
				dist[v] = dist[u] + w;
				if(!inqueue[v]) {
					inqueue[v] = true;
					q.push(v);
					count[v] = count[u] + 1;
					if(count[v] > n) {
						return {};
					}
				}
			}
		}
	}
	return dist;
}