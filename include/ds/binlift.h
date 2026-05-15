#pragma once
#include "common.h"

struct BinaryLift {
	explicit BinaryLift(int n)
		: tree(n), anc(n, vector<int>(LOG, -1)), depth(n) {}
	void addedge(int u, int v) {
		tree[u].push_back(v);
		tree[v].push_back(u);
	}
	void build(int u = 0) {
		dfs(u, -1);
	}
	int lca(int u, int v) const {
		if(depth[u] < depth[v]) swap(u, v);
		for(int k = LOG - 1; k >= 0; --k) {
			if(anc[u][k] != -1) {
				if(depth[anc[u][k]] >= depth[v]) {
					u = anc[u][k];
				}
			}
		}
		if(u == v) return u;
		for(int k = LOG - 1; k >= 0; --k) {
			if(anc[u][k] != anc[v][k]) {
				u = anc[u][k];
				v = anc[v][k];
			}
		}
		return anc[u][0];
	}
	int kth_ancestor(int x, int k) const {
		for(int i = 0; i < LOG; ++i) {
			if((k >> i) & 1) {
				x = anc[x][i];
				if(x == -1) return -1;
			}
		}
		return x;
	}
	vector<vector<int>> tree;

private:
	static constexpr int LOG = 20;
	vector<vector<int>> anc;
	vector<int> depth;
	void dfs(int u, int fa) {
		depth[u] = fa != -1 ? depth[fa] + 1 : 0;
		anc[u][0] = fa;
		for(int k = 1; k < LOG; ++k) {
			if(anc[u][k - 1] == -1) {
				anc[u][k] = -1;
			} else {
				anc[u][k] = anc[anc[u][k - 1]][k - 1];
			}
		}
		for(int v : tree[u]) {
			if(v != fa) {
				dfs(v, u);
			}
		}
	}
};
