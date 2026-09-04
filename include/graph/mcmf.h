#pragma once
#include "common.h"

constexpr ll inf = 0x3f3f3f3f3f3f3f3f;

struct MCMF {
	struct Edge {
		int v, r;
		ll w, c;
	};
	int n;
	vector<vector<Edge>> g;
	explicit MCMF(int _n) : n(_n), g(_n) {}
	void add_edge(int u, int v, ll f, ll w) {
		int iu = g[u].size(), iv = g[v].size();
		g[u].push_back({v, iv, w, f});
		g[v].push_back({u, iu, -w, 0});
	}
	pair<ll, ll> mcmf(int s, int t) {
		ll mc = 0, mf = 0;
		vector<ll> h(n, inf);
		h[s] = 0;
		for(int k = 1; k < n; ++k) {
			bool cg = false;
			for(int u = 0; u < n; ++u) {
				if(h[u] == inf) continue;
				for(auto &e : g[u]) {
					if(e.c > 0 && h[e.v] > h[u] + e.w) {
						h[e.v] = h[u] + e.w;
						cg = true;
					}
				}
			}
			if(!cg) break;
		}
		for(ll &x : h) {
			if(x == inf) x = 0;
		}
		while(true) {
			vector<int> pv(n, -1), pe(n, -1);
			vector<ll> d(n, inf);
			priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
			d[s] = 0;
			pq.emplace(0, s);
			while(!pq.empty()) {
				auto [du, u] = pq.top();
				pq.pop();
				if(du != d[u]) continue;
				for(int i = 0; i < g[u].size(); ++i) {
					const auto &e = g[u][i];
					if(e.c <= 0) continue;
					ll nd = du + e.w + h[u] - h[e.v];
					if(nd < d[e.v]) {
						d[e.v] = nd;
						pv[e.v] = u;
						pe[e.v] = i;
						pq.emplace(nd, e.v);
					}
				}
			}
			if(d[t] == inf) break;
			for(int v = 0; v < n; ++v) {
				if(d[v] != inf) h[v] += d[v];
			}
			ll add = inf;
			for(int v = t; v != s; v = pv[v]) {
				chkmin(add, g[pv[v]][pe[v]].c);
			}
			for(int v = t; v != s; v = pv[v]) {
				int u = pv[v], i = pe[v];
				int r = g[u][i].r;
				g[u][i].c -= add;
				g[v][r].c += add;
			}
			mf += add;
			mc += add * (h[t] - h[s]);
		}
		return {mc, mf};
	}
};
