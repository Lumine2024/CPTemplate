#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

int hungarian(const vector<vector<int>> &graph, int vsz) {
	int usz = graph.size();
	vector<int> mu(usz, -1);
	vector<int> mv(vsz, -1);
	auto dfs = [&](auto &&dfs, int u, vector<bool> &visited) -> bool {
		for(int v : graph[u]) {
			if(visited[v]) continue;
			visited[v] = true;
			if(mv[v] == -1 || dfs(dfs, mv[v], visited)) {
				mv[v] = u;
				mu[u] = v;
				return true;
			}
		}
		return false;
	};
	int ret = 0;
	for(int u = 0; u < usz; ++u) {
		if(mu[u] == -1) {
			vector<bool> visited(vsz, false);
			if(dfs(dfs, u, visited)) {
				ret++;
			}
		}
	}
	return ret;
}