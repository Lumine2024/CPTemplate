#pragma once
#include "common.h"

struct VirtualTree {
	vector<int> tin, tout, dep, siz;
	vector<vector<int>> g, vg;
	vector<array<int, 20>> up;
	vector<int> iv;
	int ur = -1, vr = -1;
	VirtualTree(int n)
		: tin(n, -1), tout(n, -1), dep(n, -1), siz(n, -1), g(n), vg(n), up(n) {}
	void add_edge(int u, int v) {
		g[u].push_back(v);
		g[v].push_back(u);
	}
	/*
	o_开头的函数：原图中的函数，如建原树、求LCA、判断祖先关系等
	*/
	void o_build(int r = 0) {
		ur = r;
		int timer = 0;
		[&](auto &&f) { f(f, r, -1); }([&](auto &&dfs, int u, int fa) -> void {
			tin[u] = timer++;
			dep[u] = fa == -1 ? 0 : dep[fa] + 1;
			up[u][0] = fa;
			for(int i = 1; i < 20; ++i) {
				up[u][i] = up[u][i - 1] == -1 ? -1 : up[up[u][i - 1]][i - 1];
			}
			siz[u] = 1;
			for(int v : g[u]) {
				if(v != fa) {
					dfs(dfs, v, u);
					siz[u] += siz[v];
				}
			}
			tout[u] = timer;
		});
	}
	// 注意：返回值为 u 是不是 v 的祖先
	bool o_anc(int u, int v) {
		if(u == -1) return true;
		if(v == -1) return false;
		return tin[u] <= tin[v] && tout[v] <= tout[u];
	}
	int o_lca(int u, int v) {
		if(o_anc(u, v)) return u;
		if(o_anc(v, u)) return v;
		for(int i = 19; i >= 0; --i) {
			if(!o_anc(up[u][i], v)) u = up[u][i];
		}
		return up[u][0];
	}
	/*
	v_开头的函数：虚树相关，包含清空、建虚树等
	*/
	void v_clear() {
		for(int x : iv) vg[x].clear();
		iv.clear();
		vr = -1;
	}
	void v_build(vector<int> imp) {
		v_clear();
		sort(imp.begin(), imp.end(),
			 [&](int x, int y) { return tin[x] < tin[y]; });
		imp.erase(unique(imp.begin(), imp.end()), imp.end());
		int n = imp.size();
		for(int i = 1; i < n; ++i) {
			imp.push_back(o_lca(imp[i - 1], imp[i]));
		}
		sort(imp.begin(), imp.end(),
			 [&](int x, int y) { return tin[x] < tin[y]; });
		imp.erase(unique(imp.begin(), imp.end()), imp.end());
		vector<int> stk;
		for(int x : imp) {
			while(!stk.empty() && !o_anc(stk.back(), x)) {
				stk.pop_back();
			}
			if(!stk.empty()) {
				vg[stk.back()].push_back(x);
				vg[x].push_back(stk.back());
			} else {
				vr = x;
			}
			stk.push_back(x);
		}
		iv = move(imp);
	}
};