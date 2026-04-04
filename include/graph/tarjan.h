#pragma once
#include "common.h"

template<class T>
concept EdgeT = requires(T t) {
	{ t.v } -> convertible_to<int>;
};

// 强连通分量
struct SCC {
	explicit SCC(int n) : nodes(n), graph(n) {}
	explicit SCC(const vector<vector<int>> &g) : graph(g), nodes(g.size()) {
		build();
	}
	template<EdgeT T>
	explicit SCC(const vector<vector<T>> &g)
		: graph(g.size()), nodes(g.size()) {
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
		for(int i = 0; i < nodes.size(); i++) {
			if(nodes[i].dfn == -1) dfs(dfn, cnt, i);
		}
		dag.assign(cnt, {});
		set<pair<int, int>> edges;
		for(int u = 0; u < graph.size(); ++u) {
			for(int v : graph[u]) {
				int bu = nodes[u].inscc, bv = nodes[v].inscc;
				if(bu != bv && !edges.contains({bu, bv})) {
					dag[bu].push_back(bv);
					edges.insert({bu, bv});
				}
			}
		}
	}
	struct Node {
		int dfn, low, inscc;
		bool ins;
		Node() : dfn(-1), low(-1), ins(false), inscc(-1) {}
	};
	vector<Node> nodes;
	vector<vector<int>> graph, sccs, dag;

private:
	stack<int> stk;
	void dfs(int &dfn, int &cnt, int u) {
		nodes[u].dfn = nodes[u].low = dfn++;
		stk.push(u);
		nodes[u].ins = true;
		for(int v : graph[u]) {
			if(nodes[v].dfn == -1) {
				dfs(dfn, cnt, v);
				nodes[u].low = min(nodes[u].low, nodes[v].low);
			} else if(nodes[v].ins) {
				nodes[u].low = min(nodes[u].low, nodes[v].low);
			}
		}
		if(nodes[u].dfn == nodes[u].low) {
			vector<int> scc;
			int v = -1;
			while(v != u) {
				v = stk.top();
				stk.pop();
				nodes[v].ins = false;
				nodes[v].inscc = cnt;
				scc.emplace_back(v);
			}
			sccs.emplace_back(move(scc));
			++cnt;
		}
	}
};
// 边双
struct EBCC {
	explicit EBCC(int n) : nodes(n), graph(n), in_ebcc(n) {}
	explicit EBCC(const vector<vector<int>> &g)
		: graph(g), nodes(g.size()), in_ebcc(g.size()) {
		build();
	}
	template<EdgeT T>
	explicit EBCC(const vector<vector<T>> &g)
		: graph(g.size()), nodes(g.size()), in_ebcc(g.size()) {
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
		for(int i = 0; i < nodes.size(); ++i) {
			if(nodes[i].dfn == -1) dfs(i, -1, dfn);
		}
		for(int i = 0; i < ebcc.size(); ++i) {
			for(int u : ebcc[i]) in_ebcc[u] = i;
		}
	}
	vector<vector<int>> graph;
	vector<vector<int>> ebcc;
	vector<int> in_ebcc;
	struct Node {
		int dfn, low;
		bool ins;
		Node() : dfn(-1), low(-1), ins(false) {}
	};
	vector<Node> nodes;

private:
	stack<int> stk;
	void dfs(int u, int fa, int &dfn) {
		nodes[u].dfn = nodes[u].low = dfn++;
		nodes[u].ins = true;
		stk.push(u);
		for(int v : graph[u]) {
			if(v == fa) continue;
			if(nodes[v].dfn == -1) {
				dfs(v, u, dfn);
				nodes[u].low = min(nodes[u].low, nodes[v].low);
			} else if(nodes[v].ins) {
				nodes[u].low = min(nodes[u].low, nodes[v].dfn);
			}
		}
		if(nodes[u].dfn == nodes[u].low) {
			vector<int> t;
			int n = -1;
			while(n != u) {
				n = stk.top();
				stk.pop();
				t.push_back(n);
				nodes[n].ins = false;
			}
			ebcc.emplace_back(move(t));
		}
	}
};
// 点双
struct DCC {
	explicit DCC(int n) : nodes(n), graph(n) {}
	explicit DCC(const vector<vector<int>> &g) : graph(g), nodes(g.size()) {
		build();
	}
	template<EdgeT T>
	explicit DCC(const vector<vector<T>> &g)
		: graph(g.size()), nodes(g.size()) {
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
		for(int i = 0; i < nodes.size(); ++i) {
			if(nodes[i].dfn == -1) {
				dfs(i, -1, i, dfn_now);
			}
		}
	}
	struct Node {
		int dfn, low;
		Node() : dfn(-1), low(-1) {}
	};
	vector<Node> nodes;
	vector<vector<int>> graph;
	vector<vector<int>> dcc;

private:
	stack<int> stk;
	void dfs(int u, int parent, int root, int &dfn) {
		nodes[u].dfn = nodes[u].low = dfn++;
		stk.push(u);
		int child = 0;
		for(int v : graph[u]) {
			if(v == parent) continue;
			if(nodes[v].dfn == -1) {
				dfs(v, u, root, dfn);
				nodes[u].low = min(nodes[u].low, nodes[v].low);
				if(nodes[v].low >= nodes[u].dfn) {
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
				nodes[u].low = min(nodes[u].low, nodes[v].dfn);
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
	explicit AP(int n) : nodes(n), graph(n) {}
	explicit AP(const vector<vector<int>> &g) : graph(g), nodes(g.size()) {
		build();
	}
	template<EdgeT T>
	explicit AP(const vector<vector<T>> &g) : graph(g.size()), nodes(g.size()) {
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
		for(int i = 0; i < nodes.size(); ++i) {
			if(nodes[i].dfn == -1) {
				dfs(i, -1, dfn);
			}
		}
		sort(cutpoints.begin(), cutpoints.end());
		cutpoints.erase(unique(cutpoints.begin(), cutpoints.end()),
						cutpoints.end());
	}
	struct Node {
		int dfn, low;
		Node() : dfn(-1), low(-1) {}
	};
	vector<Node> nodes;
	vector<vector<int>> graph;
	vector<int> cutpoints;

private:
	void dfs(int u, int fa, int &dfn) {
		nodes[u].dfn = nodes[u].low = dfn++;
		int child = 0;
		bool flag = false;
		for(int v : graph[u]) {
			if(nodes[v].dfn == -1) {
				++child;
				dfs(v, u, dfn);
				nodes[u].low = min(nodes[u].low, nodes[v].low);
				if(fa != -1) {
					flag |= (nodes[v].low >= nodes[u].dfn);
				}
			} else if(v != fa) {
				nodes[u].low = min(nodes[u].low, nodes[v].dfn);
			}
		}
		if(fa == -1) flag = (child > 1);
		if(flag) cutpoints.push_back(u);
	}
};
// 桥
struct Bridge {
	explicit Bridge(int n) : nodes(n), graph(n) {}
	explicit Bridge(const vector<vector<int>> &g) : graph(g), nodes(g.size()) {
		build();
	}
	template<EdgeT T>
	explicit Bridge(const vector<vector<T>> &g)
		: graph(g.size()), nodes(g.size()) {
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
		for(int i = 0; i < nodes.size(); ++i) {
			if(nodes[i].dfn == -1) dfs(i, -1, dfn);
		}
	}
	struct Node {
		int dfn;
		int low;
		Node() : dfn(-1), low(-1) {}
	};
	vector<Node> nodes;
	vector<vector<int>> graph;
	vector<pair<int, int>> bridges;

private:
	void dfs(int u, int fa, int &dfn) {
		nodes[u].dfn = nodes[u].low = dfn++;
		for(int v : graph[u]) {
			if(nodes[v].dfn == -1) {
				dfs(v, u, dfn);
				nodes[u].low = min(nodes[u].low, nodes[v].low);
				if(nodes[v].low > nodes[u].dfn) {
					bridges.emplace_back(min(u, v), max(u, v));
				}
			} else if(v != fa) {
				nodes[u].low = min(nodes[u].low, nodes[v].dfn);
			}
		}
	}
};
