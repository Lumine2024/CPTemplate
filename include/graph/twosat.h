#pragma once
#include "graph/tarjan.h"

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
		if(scc.inscc[2 * i] == scc.inscc[2 * i + 1]) return {};
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
