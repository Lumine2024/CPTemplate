#pragma once
#include "common.h"

int hungarian(const vector<vector<int>> &graph, int vsz) {
	int usz = graph.size();
	vector<int> mu(usz, -1);
	vector<int> mv(vsz, -1);
	auto dfs = [&](auto &&dfs, int u, vector<bool> &vis) -> bool {
		for(int v : graph[u]) {
			if(vis[v]) continue;
			vis[v] = true;
			if(mv[v] == -1 || dfs(dfs, mv[v], vis)) {
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
			vector<bool> vis(vsz, false);
			if(dfs(dfs, u, vis)) ret++;
		}
	}
	return ret;
}
