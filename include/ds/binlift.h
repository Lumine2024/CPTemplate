#pragma once
#include "common.h"

struct BinaryLift {
	explicit BinaryLift(int n) : tree(n), anc(n), dep(n) {
		for(auto &a : anc) a.fill(-1);
	}
	void add_edge(int u, int v) {
		tree[u].push_back(v);
		tree[v].push_back(u);
	}
	void build(int u = 0) {
		[&](auto &&dfs) {
			dfs(dfs, u, -1);
		}([&](auto &&dfs, int u, int fa) -> void {
			dep[u] = fa != -1 ? dep[fa] + 1 : 0;
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
					dfs(dfs, v, u);
				}
			}
		});
	}
	int lca(int u, int v) const {
		if(dep[u] < dep[v]) swap(u, v);
		for(int k = LOG - 1; k >= 0; --k) {
			if(anc[u][k] != -1) {
				if(dep[anc[u][k]] >= dep[v]) {
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
	vector<array<int, LOG>> anc;
	vector<int> dep;
};
