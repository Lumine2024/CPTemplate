#pragma once
#include "common.h"

// 操作后，graph就变成了最短路
void floyd(vector<vector<ll>> &g) {
	for(int k = 0; k < g.size(); ++k)
		for(int i = 0; i < g.size(); ++i)
			for(int j = 0; j < g.size(); ++j)
				if(g[i][j] > g[i][k] + g[k][j]) g[i][j] = g[i][k] + g[k][j];
}
