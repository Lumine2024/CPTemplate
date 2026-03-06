#pragma once
#include "common.h"

constexpr ll inf = 0x3f3f3f3f3f3f3f3f;

struct EK {
	struct Edge {
		int dst, rev;
		ll weight, flow;
		bool neg;
	};
	vector<vector<Edge>> graph;
	int n;
	explicit EK(int _n) : n(_n), graph(_n) {}
	void addedge(int u, int v, ll flow, ll weight) {
		int iu = graph[u].size(), iv = graph[v].size();
		graph[u].push_back({v, iv, weight, flow, false});
		graph[v].push_back({u, iu, -weight, 0, true});
	}
	pair<ll, ll> mcmf(int s, int t) {
		ll cost = 0, flow = 0;
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
				for(int i = 0; i < graph[u].size(); ++i) {
					auto &e = graph[u][i];
					int v = e.dst;
					ll f = e.flow, w = e.weight;
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
				graph[u][e].flow -= add;
				graph[v][graph[u][e].rev].flow += add;
			}
			flow += add;
			cost += add * d[t];
		}
		return {cost, flow};
	}
};
