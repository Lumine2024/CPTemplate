#pragma once
#include "common.h"

int hungarian(const vector<vector<int>> &g, int vs) {
	int us = g.size();
	vector<int> mu(us, -1);
	vector<int> mv(vs, -1);
	auto dfs = [&](auto &&dfs, int u, vector<bool> &vis) -> bool {
		for(int v : g[u]) {
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
	for(int u = 0; u < us; ++u) {
		if(mu[u] == -1) {
			vector<bool> vis(vs, false);
			if(dfs(dfs, u, vis)) ret++;
		}
	}
	return ret;
}
