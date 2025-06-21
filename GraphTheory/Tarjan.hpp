#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

// 强连通分量
struct Tarjan_SCC {
	Tarjan_SCC(int n) : nodes(n), graph(n) {}
	void addedge(int u, int v) {
		if(u == v) return;
		graph[u].push_back(v);
	}
	void solve() {
		int now_dfn = 0, scc_count = 0;
		for(int i = 0; i < nodes.size(); i++) {
			if(nodes[i].dfn == -1) {
				dfs(now_dfn, scc_count, i);
			}
		}
		dag.assign(scc_count, {});
		set<pair<int, int>> edges;
		for(int u = 0; u < graph.size(); ++u) {
			for(int v : graph[u]) {
				int bu = nodes[u].inscc, bv = nodes[v].inscc;
				if(bu != bv && !edges.contains({ bu, bv })) {
					dag[bu].emplace_back(bv);
					edges.insert({ bu, bv });
				}
			}
		}
	}
	struct Node {
		int dfn;
		int low;
		bool instack;
		int inscc;
		Node() : dfn(-1), low(-1), instack(false), inscc(-1) {}
	};
	vector<Node> nodes;
	vector<vector<int>> graph;
	vector<vector<int>> sccs;
	vector<vector<int>> dag;
private:
	stack<int> scc_stack;
	void dfs(int &now_dfn, int &scc_count, int u) {
		nodes[u].dfn = now_dfn;
		nodes[u].low = now_dfn;
		++now_dfn;
		scc_stack.push(u);
		nodes[u].instack = true;
		for(int v : graph[u]) {
			if(nodes[v].dfn == -1) {
				dfs(now_dfn, scc_count, v);
				nodes[u].low = min(nodes[u].low, nodes[v].low);
			} else if(nodes[v].instack) {
				nodes[u].low = min(nodes[u].low, nodes[v].low);
			}
		}
		if(nodes[u].dfn == nodes[u].low) {
			vector<int> scc;
			int v = -1;
			while(v != u) {
				v = scc_stack.top();
				scc_stack.pop();
				nodes[v].instack = false;
				nodes[v].inscc = scc_count;
				scc.emplace_back(v);
			}
			sccs.emplace_back(move(scc));
			++scc_count;
		}
	}
};
// 边双
struct Tarjan_BCC {
	Tarjan_BCC(int n)
		: nodes(n), graph(n) {}
	void addedge(int u, int v) {
		if(u == v) return;
		graph[u].emplace_back(v);
		graph[v].emplace_back(u);
	}
	void solve() {
		int dfn_now = 0;
		for(int i = 0; i < nodes.size(); ++i) {
			if(nodes[i].dfn == -1) {
				dfs(i, -1, dfn_now);
			}
		}
	}
	struct Node {
		int dfn;
		int low;
		bool instack;
		Node() :dfn(-1), low(-1), instack(false) {}
	};
	vector<Node> nodes;
	vector<vector<int>> graph;
	vector<vector<int>> dcc;
private:
	stack<int> stk;
	void dfs(int u, int father, int &dfn_now) {
		nodes[u].dfn = dfn_now;
		nodes[u].low = dfn_now;
		nodes[u].instack = true;
		dfn_now++;
		stk.push(u);
		for(int v : graph[u]) {
			if(v == father) continue;
			if(nodes[v].dfn == -1) {
				dfs(v, u, dfn_now);
				nodes[u].low = min(nodes[u].low, nodes[v].low);
			} else if(nodes[v].instack) {
				nodes[u].low = min(nodes[u].low, nodes[v].dfn);
			}
		}
		if(nodes[u].dfn == nodes[u].low) {
			vector<int> t;
			int n = -1;
			while(n != u) {
				n = stk.top();
				stk.pop();
				t.emplace_back(n);
				nodes[n].instack = false;
			}
			dcc.emplace_back(move(t));
		}
	}
};
// 点双
struct Tarjan_DCC {
	Tarjan_DCC(int n)
		: nodes(n), graph(n) {}
	void addedge(int u, int v) {
		if(u == v) return;
		graph[u].emplace_back(v);
		graph[v].emplace_back(u);
	}
	void solve() {
		int dfn_now = 0;
		for(int i = 0; i < nodes.size(); ++i) {
			if(nodes[i].dfn == -1) {
				dfs(i, -1, i, dfn_now);
			}
		}
	}
	struct Node {
		int dfn;
		int low;
		Node() :dfn(-1), low(-1) {}
	};
	vector<Node> nodes;
	vector<vector<int>> graph;
	vector<vector<int>> dcc;
private:
	stack<int> stk;
	void dfs(int u, int parent, int root, int &dfn_now) {
		nodes[u].dfn = dfn_now;
		nodes[u].low = dfn_now;
		dfn_now++;
		stk.push(u);
		int child = 0;
		for(int v : graph[u]) {
			if(v == parent) continue;
			if(nodes[v].dfn == -1) {
				dfs(v, u, root, dfn_now);
				nodes[u].low = min(nodes[u].low, nodes[v].low);
				if(nodes[v].low >= nodes[u].dfn) {
					++child;
					vector<int> f = { u };
					while(!stk.empty()) {
						int x = stk.top();
						stk.pop();
						f.emplace_back(x);
						if(x == v) break;
					}
					dcc.emplace_back(move(f));
				}
			} else {
				nodes[u].low = min(nodes[u].low, nodes[v].dfn);
			}
		}
		if(u == root && graph[u].empty()) {
			dcc.emplace_back(vector<int>{u});
			return;
		}
	}
};
// 割点
struct Tarjan_Cutpoint {
	Tarjan_Cutpoint(int n)
		: nodes(n), graph(n) {}
	void addedge(int u, int v) {
		graph[u].emplace_back(v);
		graph[v].emplace_back(u);
	}
	void solve() {
		int dfn_now = 0;
		for(int i = 0; i < nodes.size(); ++i) {
			if(nodes[i].dfn == -1) {
				dfs(i, -1, dfn_now);
			}
		}
		sort(cutpoints.begin(), cutpoints.end());
		cutpoints.erase(unique(cutpoints.begin(), cutpoints.end()), cutpoints.end());
	}
	struct Node {
		int dfn;
		int low;
		Node() : dfn(-1), low(-1) {}
	};
	vector<Node> nodes;
	vector<vector<int>> graph;
	vector<int> cutpoints;
private:
	void dfs(int u, int father, int &dfn_now) {
		nodes[u].dfn = dfn_now;
		nodes[u].low = dfn_now;
		dfn_now++;
		int child = 0;
		bool flag = false;
		for(int v : graph[u]) {
			if(nodes[v].dfn == -1) {
				child++;
				dfs(v, u, dfn_now);
				nodes[u].low = min(nodes[u].low, nodes[v].low);
				if(father != -1) {
					flag |= (nodes[v].low >= nodes[u].dfn);
				}
			} else if(v != father) {
				nodes[u].low = min(nodes[u].low, nodes[v].dfn);
			}
		}
		if(father == -1) {
			flag = (child > 1);
		}
		if(flag) {
			cutpoints.emplace_back(u);
		}
	}
};
// 桥
struct Tarjan_Bridge {
	Tarjan_Bridge(int n)
		: nodes(n), graph(n) {}
	void addedge(int u, int v) {
		graph[u].emplace_back(v);
		graph[v].emplace_back(u);
	}
	void solve() {
		int dfn_now = 0;
		for(int i = 0; i < nodes.size(); ++i) {
			if(nodes[i].dfn == -1) {
				dfs(i, -1, dfn_now);
			}
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
	void dfs(int u, int father, int &dfn_now) {
		nodes[u].dfn = nodes[u].low = dfn_now++;
		for(int v : graph[u]) {
			if(nodes[v].dfn == -1) {
				dfs(v, u, dfn_now);
				nodes[u].low = min(nodes[u].low, nodes[v].low);
				if(nodes[v].low > nodes[u].dfn) {
					bridges.emplace_back(min(u, v), max(u, v));
				}
			} else if(v != father) {
				nodes[u].low = min(nodes[u].low, nodes[v].dfn);
			}
		}
	}
};