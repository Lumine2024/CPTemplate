#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
namespace _increment {
constexpr int LOG = 20;
}
struct Increment {
	Increment(int n)
		: tree(n), anc(n, vector<int>(_increment::LOG, -1)), depth(n) {}
	void addedge(int u, int v) {
		tree[u].push_back(v);
		tree[v].push_back(u);
	}
	void build(int root) {
		dfs(root, -1);
	}
	int lca(int u, int v) {
		if(depth[u] < depth[v]) swap(u, v);
		for(int k = _increment::LOG - 1; k >= 0; --k) {
			if(anc[u][k] != -1) {
				if(depth[anc[u][k]] >= depth[v]) {
					u = anc[u][k];
				}
			}
		}
		if(u == v) return u;
		for(int k = _increment::LOG - 1; k >= 0; --k) {
			if(anc[u][k] != anc[v][k]) {
				u = anc[u][k];
				v = anc[v][k];
			}
		}
		return anc[u][0];
	}
	int kth_ancestor(int x, int k) {
		for(int i = 0; i < _increment::LOG; ++i) {
			if((k >> i) & 1) {
				x = anc[x][i];
				if(x == -1) return -1;
			}
		}
		return x;
	}
	vector<vector<int>> tree;
private:
	vector<vector<int>> anc;
	vector<int> depth;
	void dfs(int root, int fa) {
		depth[root] = fa != -1 ? depth[fa] + 1 : 0;
		anc[root][0] = fa;
		for(int k = 1; k < _increment::LOG; ++k) {
			if(anc[root][k - 1] == -1) {
				anc[root][k] = -1;
			} else {
				anc[root][k] = anc[anc[root][k - 1]][k - 1];
			}
		}
		for(const int v : tree[root]) {
			if(v != fa) {
				dfs(v, root);
			}
		}
	}
};