#pragma once
#include "common.h"

struct MstCaseEdge {
	int u, v;
	ll w;
};

struct MstCase {
	const char *name;
	int n;
	vector<MstCaseEdge> edges;
	ll expected;
};

inline vector<MstCase> mst_cases() {
	return {
		{"simple_triangle", 3, {{0, 1, 1}, {1, 2, 2}, {0, 2, 3}}, 3},
		{"disconnected", 4, {{0, 1, 5}, {2, 3, 7}}, inf},
		{"single_node", 1, {}, 0},
		{"square_with_diagonal",
		 4,
		 {{0, 1, 1}, {1, 2, 2}, {2, 3, 3}, {3, 0, 4}, {0, 2, 5}},
		 6},
		{"complete_graph",
		 4,
		 {{0, 1, 10}, {0, 2, 6}, {0, 3, 5}, {1, 2, 15}, {1, 3, 4}, {2, 3, 12}},
		 15},
	};
}
