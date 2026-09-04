#pragma once
#include "common.h"

struct HLD {
	explicit HLD(int n)
		: tree(n), dfn(n), dep(n), fa(n), toc(n), sz(n), hs(n, -1) {}
	explicit HLD(const vector<vector<int>> &edges, int r = 0)
		: tree(edges), dfn(edges.size()), dep(edges.size()), fa(edges.size()),
		  toc(edges.size()), sz(edges.size()), hs(edges.size(), -1) {
		build(r);
	}
	void add_edge(int u, int v) {
		tree[u].push_back(v);
		tree[v].push_back(u);
	}
	void build(int r = 0) {
		[&](auto &&dfs) {
			dfs(dfs, r, -1);
		}([&](auto &&dfs, int x, int f) -> void {
			dep[x] = f == -1 ? 0 : dep[f] + 1;
			fa[x] = f;
			sz[x] = 1;
			hs[x] = -1;
			for(int next : tree[x]) {
				if(next == f) continue;
				dfs(dfs, next, x);
				sz[x] += sz[next];
				if(hs[x] == -1 || sz[hs[x]] < sz[next]) {
					hs[x] = next;
				}
			}
		});
		int now = 0;
		[&](auto &&dfs) {
			dfs(dfs, r, -1, r);
		}([&](auto &&dfs, int x, int f, int top) -> void {
			dfn[x] = now++;
			toc[x] = top;
			if(hs[x] == -1) return;
			dfs(dfs, hs[x], x, top);
			for(int next : tree[x]) {
				if(next != hs[x] && next != f) {
					dfs(dfs, next, x, next);
				}
			}
		});
	}
	int lca(int u, int v) const {
		while(toc[u] != toc[v]) {
			if(dep[toc[u]] < dep[toc[v]]) {
				v = fa[toc[v]];
			} else {
				u = fa[toc[u]];
			}
		}
		return dep[u] < dep[v] ? u : v;
	}
	// 返回在这个路径上的连续区间，注意左闭右开
	vector<pair<int, int>> query_path(int u, int v) const {
		vector<pair<int, int>> up, down;
		while(toc[u] != toc[v]) {
			if(dep[toc[u]] < dep[toc[v]]) {
				down.emplace_back(dfn[toc[v]], dfn[v] + 1);
				v = fa[toc[v]];
			} else {
				up.emplace_back(dfn[toc[u]], dfn[u] + 1);
				u = fa[toc[u]];
			}
		}
		if(dep[u] < dep[v]) {
			down.emplace_back(dfn[u], dfn[v] + 1);
		} else {
			up.emplace_back(dfn[v], dfn[u] + 1);
		}
		reverse(down.begin(), down.end());
		up.insert(up.end(), down.begin(), down.end());
		return up;
	}
	// 返回子树的连续区间，注意左闭右开
	pair<int, int> query_subtree(int x) const {
		return {dfn[x], dfn[x] + sz[x]};
	}
	int size(int x) const {
		return sz[x];
	}

	vector<vector<int>> tree;
	vector<int> dfn, dep, fa, toc, sz, hs;
};
