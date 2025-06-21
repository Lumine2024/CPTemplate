#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

// 操作后，graph就变成了最短路
void floyd(vector<vector<ll>> &graph) {
	for(int k = 0; k < graph.size(); ++k) {
		for(int i = 0; i < graph.size(); ++i) {
			for(int j = 0; j < graph.size(); ++j) {
				if(graph[i][j] > graph[i][k] + graph[k][j]) {
					graph[i][j] = graph[i][k] + graph[k][j];
				}
			}
		}
	}
}