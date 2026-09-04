#pragma once
#include "common.h"

template<class T>
concept EdgeT = requires(T t) {
	{ t.v } -> convertible_to<int>;
};

// Strongly connected components
struct SCC {
	explicit SCC(int n) : dfn(n, -1), low(n, -1), inscc(n, -1), ins(n), g(n) {}
	explicit SCC(const vector<vector<int>> &g)
		: dfn(g.size(), -1), low(g.size(), -1), inscc(g.size(), -1),
		  ins(g.size()), g(g) {
		build();
	}
	template<EdgeT T>
	explicit SCC(const vector<vector<T>> &g)
		: dfn(g.size(), -1), low(g.size(), -1), inscc(g.size(), -1),
		  g(g.size()) {
		int n = g.size();
		for(int u = 0; u < n; ++u) {
			for(const T &edge : g[u]) add_edge(u, edge.v);
		}
		build();
	}
	void add_edge(int u, int v) {
		if(u != v) g[u].push_back(v);
	}
	void build() {
		int ndfn = 0, cnt = 0;
		[&](auto &&dfs) {
			for(int i = 0; i < g.size(); i++) {
				if(dfn[i] == -1) dfs(dfs, i);
			}
		}([&](auto &&dfs, int u) -> void {
			dfn[u] = low[u] = ndfn++;
			stk.push(u);
			ins[u] = true;
			for(int v : g[u]) {
				if(dfn[v] == -1) {
					dfs(dfs, v);
					low[u] = min(low[u], low[v]);
				} else if(ins[v]) {
					low[u] = min(low[u], dfn[v]);
				}
			}
			if(dfn[u] == low[u]) {
				vector<int> scc;
				int v = -1;
				while(v != u) {
					v = stk.top();
					stk.pop();
					ins[v] = false;
					inscc[v] = cnt;
					scc.emplace_back(v);
				}
				sccs.emplace_back(move(scc));
				++cnt;
			}
		});
		dag.assign(cnt, {});
		set<pair<int, int>> edges;
		for(int u = 0; u < g.size(); ++u) {
			for(int v : g[u]) {
				int bu = inscc[u], bv = inscc[v];
				if(bu != bv && !edges.contains({bu, bv})) {
					dag[bu].push_back(bv);
					edges.insert({bu, bv});
				}
			}
		}
	}
	vector<int> dfn, low, inscc;
	vector<vector<int>> g, sccs, dag;

private:
	vector<bool> ins;
	stack<int> stk;
};

// Edge-biconnected components
struct EBCC {
	explicit EBCC(int n) : dfn(n, -1), low(n, -1), g(n), in_ebcc(n) {}
	explicit EBCC(const vector<vector<int>> &g)
		: dfn(g.size(), -1), low(g.size(), -1), g(g), in_ebcc(g.size()) {
		build();
	}
	template<EdgeT T>
	explicit EBCC(const vector<vector<T>> &g)
		: dfn(g.size(), -1), low(g.size(), -1), g(g.size()), in_ebcc(g.size()) {
		int n = g.size();
		for(int u = 0; u < n; ++u) {
			for(const T &edge : g[u]) add_edge(u, edge.v);
		}
		build();
	}
	void add_edge(int u, int v) {
		if(u == v) return;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	void build() {
		int ndfn = 0;
		vector<bool> ins(dfn.size(), false);
		stack<int> stk;
		[&](auto &&dfs) {
			for(int i = 0; i < g.size(); ++i) {
				if(dfn[i] == -1) dfs(dfs, i, -1);
			}
		}([&](auto &&dfs, int u, int fa) -> void {
			dfn[u] = low[u] = ndfn++;
			ins[u] = true;
			stk.push(u);
			for(int v : g[u]) {
				if(v == fa) continue;
				if(dfn[v] == -1) {
					dfs(dfs, v, u);
					low[u] = min(low[u], low[v]);
				} else if(ins[v]) {
					low[u] = min(low[u], dfn[v]);
				}
			}
			if(dfn[u] == low[u]) {
				vector<int> t;
				int n = -1;
				while(n != u) {
					n = stk.top();
					stk.pop();
					t.push_back(n);
					ins[n] = false;
				}
				ebcc.emplace_back(move(t));
			}
		});
		for(int i = 0; i < ebcc.size(); ++i) {
			for(int u : ebcc[i]) in_ebcc[u] = i;
		}
	}
	vector<vector<int>> g, ebcc;
	vector<int> in_ebcc, dfn, low;
};

// Vertex-biconnected components
struct DCC {
	explicit DCC(int n) : dfn(n, -1), low(n, -1), g(n) {}
	explicit DCC(const vector<vector<int>> &g)
		: dfn(g.size(), -1), low(g.size(), -1), g(g) {
		build();
	}
	template<EdgeT T>
	explicit DCC(const vector<vector<T>> &g)
		: dfn(g.size(), -1), low(g.size(), -1), g(g.size()) {
		int n = g.size();
		for(int u = 0; u < n; ++u) {
			for(const T &edge : g[u]) add_edge(u, edge.v);
		}
		build();
	}
	void add_edge(int u, int v) {
		if(u == v) return;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	void build() {
		int ndfn = 0;
		stack<int> stk;
		[&](auto &&dfs) {
			for(int i = 0; i < g.size(); ++i) {
				if(dfn[i] == -1) dfs(dfs, i, -1, i);
			}
		}([&](auto &&dfs, int u, int fa, int rt) -> void {
			dfn[u] = low[u] = ndfn++;
			stk.push(u);
			int child = 0;
			for(int v : g[u]) {
				if(v == fa) continue;
				if(dfn[v] == -1) {
					dfs(dfs, v, u, rt);
					low[u] = min(low[u], low[v]);
					if(low[v] >= dfn[u]) {
						++child;
						vector<int> f = {u};
						while(!stk.empty()) {
							int x = stk.top();
							stk.pop();
							f.push_back(x);
							if(x == v) break;
						}
						dcc.emplace_back(move(f));
					}
				} else {
					low[u] = min(low[u], dfn[v]);
				}
			}
			if(u == rt && g[u].empty()) {
				dcc.push_back(vector<int>{u});
				return;
			}
		});
	}
	vector<int> dfn, low;
	vector<vector<int>> g, dcc;
};

// Articulation points
struct AP {
	explicit AP(int n) : dfn(n, -1), low(n, -1), g(n) {}
	explicit AP(const vector<vector<int>> &g)
		: dfn(g.size(), -1), low(g.size(), -1), g(g) {
		build();
	}
	template<EdgeT T>
	explicit AP(const vector<vector<T>> &g)
		: dfn(g.size(), -1), low(g.size(), -1), g(g.size()) {
		int n = g.size();
		for(int u = 0; u < n; ++u) {
			for(const T &edge : g[u]) add_edge(u, edge.v);
		}
		build();
	}
	void add_edge(int u, int v) {
		g[u].push_back(v);
		g[v].push_back(u);
	}
	void build() {
		int ndfn = 0;
		[&](auto &&dfs) {
			for(int i = 0; i < g.size(); ++i) {
				if(dfn[i] == -1) dfs(dfs, i, -1);
			}
		}([&](auto &&dfs, int u, int fa) -> void {
			dfn[u] = low[u] = ndfn++;
			int child = 0;
			bool flag = false;
			for(int v : g[u]) {
				if(dfn[v] == -1) {
					++child;
					dfs(dfs, v, u);
					low[u] = min(low[u], low[v]);
					if(fa != -1) {
						flag |= (low[v] >= dfn[u]);
					}
				} else if(v != fa) {
					low[u] = min(low[u], dfn[v]);
				}
			}
			if(fa == -1) flag = (child > 1);
			if(flag) ap.push_back(u);
		});
		sort(ap.begin(), ap.end());
		ap.erase(unique(ap.begin(), ap.end()), ap.end());
	}
	vector<int> dfn, low;
	vector<vector<int>> g;
	vector<int> ap;
};

// Bridges
struct Bridge {
	explicit Bridge(int n) : dfn(n, -1), low(n, -1), g(n) {}
	explicit Bridge(const vector<vector<int>> &g)
		: dfn(g.size(), -1), low(g.size(), -1), g(g) {
		build();
	}
	template<EdgeT T>
	explicit Bridge(const vector<vector<T>> &g)
		: dfn(g.size(), -1), low(g.size(), -1), g(g.size()) {
		int n = g.size();
		for(int u = 0; u < n; ++u) {
			for(const T &edge : g[u]) add_edge(u, edge.v);
		}
		build();
	}
	void add_edge(int u, int v) {
		g[u].push_back(v);
		g[v].push_back(u);
	}
	void build() {
		int ndfn = 0;
		[&](auto &&dfs) {
			for(int i = 0; i < g.size(); ++i) {
				if(dfn[i] == -1) dfs(dfs, i, -1);
			}
		}([&](auto &&dfs, int u, int fa) -> void {
			dfn[u] = low[u] = ndfn++;
			for(int v : g[u]) {
				if(dfn[v] == -1) {
					dfs(dfs, v, u);
					low[u] = min(low[u], low[v]);
					if(low[v] > dfn[u]) {
						bridges.emplace_back(min(u, v), max(u, v));
					}
				} else if(v != fa) {
					low[u] = min(low[u], dfn[v]);
				}
			}
		});
	}
	vector<int> dfn, low;
	vector<vector<int>> g;
	vector<pair<int, int>> bridges;
};
