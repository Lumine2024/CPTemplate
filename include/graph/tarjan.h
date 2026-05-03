#pragma once
#include "common.h"

template<class T>
concept EdgeT = requires(T t) {
	{ t.v } -> convertible_to<int>;
};

// 强连通分量
struct SCC {
	explicit SCC(int n)
		: dfn(n, -1), low(n, -1), inscc(n, -1), ins(n), graph(n) {}
	explicit SCC(const vector<vector<int>> &g)
		: dfn(g.size(), -1), low(g.size(), -1), inscc(g.size(), -1),
		  ins(g.size()), graph(g) {
		build();
	}
	template<EdgeT T>
	explicit SCC(const vector<vector<T>> &g)
		: dfn(g.size(), -1), low(g.size(), -1), inscc(g.size(), -1),
		  ins(g.size()), graph(g.size()) {
		int n = g.size();
		for(int u = 0; u < n; ++u) {
			for(const T &edge : g[u]) addedge(u, edge.v);
		}
		build();
	}
	void addedge(int u, int v) {
		if(u != v) graph[u].push_back(v);
	}
	void build() {
		int dfn = 0, cnt = 0;
		for(int i = 0; i < graph.size(); i++) {
			if(this->dfn[i] == -1) dfs(dfn, cnt, i);
		}
		dag.assign(cnt, {});
		set<pair<int, int>> edges;
		for(int u = 0; u < graph.size(); ++u) {
			for(int v : graph[u]) {
				int bu = inscc[u], bv = inscc[v];
				if(bu != bv && !edges.contains({bu, bv})) {
					dag[bu].push_back(bv);
					edges.insert({bu, bv});
				}
			}
		}
	}
	vector<int> dfn, low, inscc;
	vector<bool> ins;
	vector<vector<int>> graph, sccs, dag;

private:
	stack<int> stk;
	void dfs(int &dfn, int &cnt, int u) {
		this->dfn[u] = low[u] = dfn++;
		stk.push(u);
		ins[u] = true;
		for(int v : graph[u]) {
			if(this->dfn[v] == -1) {
				dfs(dfn, cnt, v);
				low[u] = min(low[u], low[v]);
			} else if(ins[v]) {
				low[u] = min(low[u], low[v]);
			}
		}
		if(this->dfn[u] == low[u]) {
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
	}
};
// 边双
struct EBCC {
	explicit EBCC(int n)
		: dfn(n, -1), low(n, -1), ins(n), graph(n), in_ebcc(n) {}
	explicit EBCC(const vector<vector<int>> &g)
		: dfn(g.size(), -1), low(g.size(), -1), ins(g.size()), graph(g),
		  in_ebcc(g.size()) {
		build();
	}
	template<EdgeT T>
	explicit EBCC(const vector<vector<T>> &g)
		: dfn(g.size(), -1), low(g.size(), -1), ins(g.size()),
		  graph(g.size()), in_ebcc(g.size()) {
		int n = g.size();
		for(int u = 0; u < n; ++u) {
			for(const T &edge : g[u]) addedge(u, edge.v);
		}
		build();
	}
	void addedge(int u, int v) {
		if(u == v) return;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	void build() {
		int dfn = 0;
		for(int i = 0; i < graph.size(); ++i) {
			if(this->dfn[i] == -1) dfs(i, -1, dfn);
		}
		for(int i = 0; i < ebcc.size(); ++i) {
			for(int u : ebcc[i]) in_ebcc[u] = i;
		}
	}
	vector<vector<int>> graph;
	vector<vector<int>> ebcc;
	vector<int> in_ebcc;
	vector<int> dfn, low;
	vector<bool> ins;

private:
	stack<int> stk;
	void dfs(int u, int fa, int &dfn) {
		this->dfn[u] = low[u] = dfn++;
		ins[u] = true;
		stk.push(u);
		for(int v : graph[u]) {
			if(v == fa) continue;
			if(this->dfn[v] == -1) {
				dfs(v, u, dfn);
				low[u] = min(low[u], low[v]);
			} else if(ins[v]) {
				low[u] = min(low[u], this->dfn[v]);
			}
		}
		if(this->dfn[u] == low[u]) {
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
	}
};
// 点双
struct DCC {
	explicit DCC(int n) : dfn(n, -1), low(n, -1), graph(n) {}
	explicit DCC(const vector<vector<int>> &g)
		: dfn(g.size(), -1), low(g.size(), -1), graph(g) {
		build();
	}
	template<EdgeT T>
	explicit DCC(const vector<vector<T>> &g)
		: dfn(g.size(), -1), low(g.size(), -1), graph(g.size()) {
		int n = g.size();
		for(int u = 0; u < n; ++u) {
			for(const T &edge : g[u]) addedge(u, edge.v);
		}
		build();
	}
	void addedge(int u, int v) {
		if(u == v) return;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	void build() {
		int dfn_now = 0;
		for(int i = 0; i < graph.size(); ++i) {
			if(dfn[i] == -1) {
				dfs(i, -1, i, dfn_now);
			}
		}
	}
	vector<int> dfn, low;
	vector<vector<int>> graph;
	vector<vector<int>> dcc;

private:
	stack<int> stk;
	void dfs(int u, int parent, int root, int &dfn) {
		this->dfn[u] = low[u] = dfn++;
		stk.push(u);
		int child = 0;
		for(int v : graph[u]) {
			if(v == parent) continue;
			if(this->dfn[v] == -1) {
				dfs(v, u, root, dfn);
				low[u] = min(low[u], low[v]);
				if(low[v] >= this->dfn[u]) {
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
				low[u] = min(low[u], this->dfn[v]);
			}
		}
		if(u == root && graph[u].empty()) {
			dcc.push_back(vector<int>{u});
			return;
		}
	}
};
// 割点
struct AP {
	explicit AP(int n) : dfn(n, -1), low(n, -1), graph(n) {}
	explicit AP(const vector<vector<int>> &g)
		: dfn(g.size(), -1), low(g.size(), -1), graph(g) {
		build();
	}
	template<EdgeT T> explicit AP(const vector<vector<T>> &g)
		: dfn(g.size(), -1), low(g.size(), -1), graph(g.size()) {
		int n = g.size();
		for(int u = 0; u < n; ++u) {
			for(const T &edge : g[u]) addedge(u, edge.v);
		}
		build();
	}
	void addedge(int u, int v) {
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	void build() {
		int dfn = 0;
		for(int i = 0; i < graph.size(); ++i) {
			if(this->dfn[i] == -1) {
				dfs(i, -1, dfn);
			}
		}
		sort(cutpoints.begin(), cutpoints.end());
		cutpoints.erase(unique(cutpoints.begin(), cutpoints.end()),
						cutpoints.end());
	}
	vector<int> dfn, low;
	vector<vector<int>> graph;
	vector<int> cutpoints;

private:
	void dfs(int u, int fa, int &dfn) {
		this->dfn[u] = low[u] = dfn++;
		int child = 0;
		bool flag = false;
		for(int v : graph[u]) {
			if(this->dfn[v] == -1) {
				++child;
				dfs(v, u, dfn);
				low[u] = min(low[u], low[v]);
				if(fa != -1) {
					flag |= (low[v] >= this->dfn[u]);
				}
			} else if(v != fa) {
				low[u] = min(low[u], this->dfn[v]);
			}
		}
		if(fa == -1) flag = (child > 1);
		if(flag) cutpoints.push_back(u);
	}
};
// 桥
struct Bridge {
	explicit Bridge(int n) : dfn(n, -1), low(n, -1), graph(n) {}
	explicit Bridge(const vector<vector<int>> &g)
		: dfn(g.size(), -1), low(g.size(), -1), graph(g) {
		build();
	}
	template<EdgeT T>
	explicit Bridge(const vector<vector<T>> &g)
		: dfn(g.size(), -1), low(g.size(), -1), graph(g.size()) {
		int n = g.size();
		for(int u = 0; u < n; ++u) {
			for(const T &edge : g[u]) addedge(u, edge.v);
		}
		build();
	}
	void addedge(int u, int v) {
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	void build() {
		int dfn = 0;
		for(int i = 0; i < graph.size(); ++i) {
			if(this->dfn[i] == -1) dfs(i, -1, dfn);
		}
	}
	vector<int> dfn, low;
	vector<vector<int>> graph;
	vector<pair<int, int>> bridges;

private:
	void dfs(int u, int fa, int &dfn) {
		this->dfn[u] = low[u] = dfn++;
		for(int v : graph[u]) {
			if(this->dfn[v] == -1) {
				dfs(v, u, dfn);
				low[u] = min(low[u], low[v]);
				if(low[v] > this->dfn[u]) {
					bridges.emplace_back(min(u, v), max(u, v));
				}
			} else if(v != fa) {
				low[u] = min(low[u], this->dfn[v]);
			}
		}
	}
};
