#pragma once
#include "common.h"

// 强连通分量
struct SCC {
	explicit SCC(int n) : nodes(n), graph(n) {}
	void addedge(int u, int v) {
		if(u == v) return;
		graph[u].push_back(v);
	}
	void build() {
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
				if(bu != bv && !edges.contains({bu, bv})) {
					dag[bu].emplace_back(bv);
					edges.insert({bu, bv});
				}
			}
		}
	}
	struct Node {
		int dfn, low, inscc;
		bool instk;
		Node() : dfn(-1), low(-1), inscc(-1), instk(false) {}
	};
	vector<Node> nodes;
	vector<vector<int>> sccs, dag;

private:
	vector<vector<int>> graph;
	stack<int> st;
	void dfs(int &dfn, int &cnt, int u) {
		nodes[u].dfn = nodes[u].low = dfn++;
		nodes[u].instk = true;
		st.push(u);
		for(int v : graph[u]) {
			if(nodes[v].dfn == -1) {
				dfs(dfn, cnt, v);
				chkmin(nodes[u].low, nodes[v].low);
			} else if(nodes[v].instk) {
				chkmin(nodes[u].low, nodes[v].dfn);
			}
		}
		if(nodes[u].dfn == nodes[u].low) {
			vector<int> scc;
			while(true) {
				int v = st.top();
				st.pop();
				nodes[v].inscc = cnt;
				nodes[v].instk = false;
				scc.push_back(v);
				if(v == u) break;
			}
			sccs.push_back(scc);
			++cnt;
		}
	}
};

// 本题给的是析取式，在这里我转化为了蕴含式求解
// 请打一个SCC下来
// 注意：蕴含式也要加另一条边，A->B要加B'->A'
vector<int> twosat(int n, const vector<tuple<int, int, int, int>> &conds) {
	SCC scc(2 * n);
	for(auto [i, fi, j, fj] : conds) {
		scc.addedge(2 * i + 1 - fi, 2 * j + fj);
		scc.addedge(2 * j + 1 - fj, 2 * i + fi);
	}
	scc.build();
	for(int i = 0; i < n; ++i) {
		if(scc.nodes[2 * i].inscc == scc.nodes[2 * i + 1].inscc) return {};
	}
	vector<int> ans(n, -1);
	for(int i = 0; i < scc.sccs.size(); ++i) {
		for(int ii : scc.sccs[i]) {
			int u = ii / 2;
			int v = ii % 2;
			if(ans[u] == -1) ans[u] = v;
		}
	}
	return ans;
}
