#pragma once
#include "common.h"

constexpr ll inf = 0x3f3f3f3f3f3f3f3f;

struct Dinic {
	struct Edge {
		int v, r;
		ll w;
	};
	vector<vector<Edge>> g;
	Dinic(int n, int s = -1, int t = -1) : g(n), lv(n), _s(s), _t(t), n(n) {}
	void add_edge(int u, int v, ll w) {
		int iv = g[v].size(), iu = g[u].size();
		g[u].push_back({v, iv, w});
		g[v].push_back({u, iu, 0});
	}
	ll maxflow(int s = -1, int t = -1) {
		if(_s == -1) _s = s;
		if(_t == -1) _t = t;
		ll mf = 0;
		auto dfs = [&](auto &&dfs, int u, ll mf) -> ll {
			if(u == _t || mf == 0) return mf;
			ll nf = 0;
			for(auto &e : g[u]) {
				if(lv[e.v] == lv[u] + 1 && e.w > 0) {
					ll min_flow = min(mf, e.w);
					ll push = dfs(dfs, e.v, min_flow);
					if(push > 0) {
						e.w -= push;
						g[e.v][e.r].w += push;
						nf += push;
						mf -= push;
						if(mf == 0) return nf;
					}
				}
			}
			return nf;
		};
		while(bfs()) {
			ll flow = dfs(dfs, _s, inf);
			while(flow > 0) {
				mf += flow;
				flow = dfs(dfs, _s, inf);
			}
		}
		return mf;
	}

private:
	vector<int> lv;
	int n, _s, _t;
	bool bfs() {
		fill(lv.begin(), lv.end(), -1);
		lv[_s] = 0;
		queue<int> q;
		q.emplace(_s);
		while(!q.empty()) {
			int u = q.front();
			q.pop();
			for(const auto &e : g[u]) {
				if(lv[e.v] == -1 && e.w > 0) {
					lv[e.v] = lv[u] + 1;
					q.emplace(e.v);
				}
			}
		}
		return lv[_t] != -1;
	}
};
