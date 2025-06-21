#pragma once
#include <bits/stdc++.h>
#include "GraphTheory/Tarjan.hpp"
using namespace std;
using ll = long long;
using ull = unsigned long long;

// 本题给的是析取式，在这里我转化为了蕴含式求解
// 请打一个Tarjan_SCC下来
// 注意：蕴含式也要加另一条边，A->B要加B'->A'
void solve_twosat() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	Tarjan_SCC solver(2 * n);
	for(int _ = 0; _ < m; ++_) {
		int i, flag_i, j, flag_j;
		cin >> i >> flag_i >> j >> flag_j;
		--i;
		--j;
		solver.addedge(2 * i + 1 - flag_i, 2 * j + flag_j);
		solver.addedge(2 * j + 1 - flag_j, 2 * i + flag_i);
	}
	solver.solve();
	for(int i = 0; i < n; ++i) {
		if(solver.nodes[2 * i].inscc == solver.nodes[2 * i + 1].inscc) {
			cout << "IMPOSSIBLE\n";
			return;
		}
	}
	cout << "POSSIBLE\n";
	vector<int> ans(n, -1);
	for(int i = 0; i < solver.sccs.size(); ++i) {
		for(int ii : solver.sccs[i]) {
			int u = ii / 2;
			int v = ii % 2;
			if(ans[u] == -1) {
				ans[u] = v;
			}
		}
	}
	for(int i : ans) {
		cout << i << ' ';
	}
}