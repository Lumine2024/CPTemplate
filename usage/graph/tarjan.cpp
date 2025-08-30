
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;

template<class T, class F> concept binary_func = convertible_to<F, function<bool(T, T)>>;
template<class T1, class T2, class F> requires(binary_func<T1, F> &&convertible_to<T2, T1>) bool chkf(T1 &x, const T2 &y, F &&f) {
	if(f(static_cast<T1>(y), x)) {
		x = static_cast<T1>(y);
		return true;
	}
	return false;
}
template<class T1, class T2> bool chkmin(T1 &x, const T2 &y) {
	return chkf(x, y, less<T1>{});
}
template<class T1, class T2> bool chkmax(T1 &x, const T2 &y) {
	return chkf(x, y, greater<T1>{});
}

// 强连通分量
struct SCC {
	explicit SCC(int n) : nodes(n), graph(n) {}
	explicit SCC(const vector<vector<int>> &g) : graph(g), nodes(g.size()) {
		solve();
	}
	void addedge(int u, int v) {
		if(u == v) return;
		graph[u].push_back(v);
	}
	void solve() {
		int dfn = 0, cnt = 0;
		for(int i = 0; i < nodes.size(); i++) {
			if(nodes[i].dfn == -1) {
				dfs(dfn, cnt, i);
			}
		}
		dag.assign(cnt, {});
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
		bool ins;
		int inscc;
		Node() : dfn(-1), low(-1), ins(false), inscc(-1) {}
	};
	vector<Node> nodes;
	vector<vector<int>> graph, sccs, dag;
private:
	stack<int> scc_stack;
	void dfs(int &dfn, int &cnt, int u) {
		nodes[u].dfn = dfn;
		nodes[u].low = dfn;
		++dfn;
		scc_stack.push(u);
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
				v = scc_stack.top();
				scc_stack.pop();
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
	explicit EBCC(const vector<vector<int>> &g) : graph(g), nodes(g.size()), in_ebcc(g.size()) {
		solve();
	}
	void addedge(int u, int v) {
		if(u == v) return;
		graph[u].emplace_back(v);
		graph[v].emplace_back(u);
	}
	void solve() {
		int dfn = 0;
		for(int i = 0; i < nodes.size(); ++i) {
			if(nodes[i].dfn == -1) {
				dfs(i, -1, dfn);
			}
		}
		for(int i = 0; i < ebcc.size(); ++i) {
			for(int u : ebcc[i]) {
				in_ebcc[u] = i;
			}
		}
	}
	vector<vector<int>> graph;
	vector<vector<int>> ebcc;
	vector<int> in_ebcc;
private:
	struct Node {
		int dfn;
		int low;
		bool ins;
		Node() : dfn(-1), low(-1), ins(false) {}
	};
	vector<Node> nodes;
	stack<int> stk;
	void dfs(int u, int fa, int &dfn) {
		nodes[u].dfn = nodes[u].low = dfn;
		nodes[u].ins = true;
		dfn++;
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
				t.emplace_back(n);
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
		solve();
	}
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
struct Cutpoint {
	explicit Cutpoint(int n) : nodes(n), graph(n) {}
	explicit Cutpoint(const vector<vector<int>> &g) : graph(g), nodes(g.size()) {
		solve();
	}
	void addedge(int u, int v) {
		graph[u].emplace_back(v);
		graph[v].emplace_back(u);
	}
	void solve() {
		int dfn = 0;
		for(int i = 0; i < nodes.size(); ++i) {
			if(nodes[i].dfn == -1) {
				dfs(i, -1, dfn);
			}
		}
		sort(cutpoints.begin(), cutpoints.end());
		cutpoints.erase(unique(cutpoints.begin(), cutpoints.end()), cutpoints.end());
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
		if(fa == -1) {
			flag = (child > 1);
		}
		if(flag) {
			cutpoints.emplace_back(u);
		}
	}
};
// 桥
struct Bridge {
	explicit Bridge(int n) : nodes(n), graph(n) {}
	explicit Bridge(const vector<vector<int>> &g) : graph(g), nodes(g.size()) {
		solve();
	}
	void addedge(int u, int v) {
		graph[u].emplace_back(v);
		graph[v].emplace_back(u);
	}
	void solve() {
		int dfn = 0;
		for(int i = 0; i < nodes.size(); ++i) {
			if(nodes[i].dfn == -1) {
				dfs(i, -1, dfn);
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

inline void solve() {
    
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
