#pragma once
#include "common.h"

constexpr ll inf = 0x3f3f3f3f3f3f3f3f;

struct EK {
	struct Edge {
		int v, r;
		ll w, c;
		bool neg;
	};
	vector<vector<Edge>> g;
	int n;
	explicit EK(int _n) : n(_n), g(_n) {}
	void addedge(int u, int v, ll f, ll w) {
		int iu = g[u].size(), iv = g[v].size();
		g[u].push_back({v, iv, w, f, false});
		g[v].push_back({u, iu, -w, 0, true});
	}
	pair<ll, ll> mcmf(int s, int t) {
		ll sw = 0, sf = 0;
		while(true) {
			vector<int> pv(n, -1), pe(n, -1);
			vector<ll> d(n, inf), mf(n, 0);
			vector<bool> inq(n, false);
			queue<int> q;
			q.push(s);
			d[s] = 0;
			mf[s] = inf;
			inq[s] = true;
			while(!q.empty()) {
				int u = q.front();
				q.pop();
				inq[u] = false;
				for(int i = 0; i < g[u].size(); ++i) {
					auto &e = g[u][i];
					int v = e.v;
					ll f = e.c, w = e.w;
					if(f > 0 && d[u] + w < d[v]) {
						d[v] = d[u] + w;
						pv[v] = u;
						pe[v] = i;
						mf[v] = min(mf[u], f);
						if(!inq[v]) {
							q.push(v);
							inq[v] = true;
						}
					}
				}
			}
			if(mf[t] <= 0) break;
			ll add = mf[t];
			for(int v = t; v != s; v = pv[v]) {
				int u = pv[v], e = pe[v];
				g[u][e].c -= add;
				g[v][g[u][e].r].c += add;
			}
			sf += add;
			sw += add * d[t];
		}
		return {sw, sf};
	}
};
