#pragma once
#include "graph/edge.h"

struct ShortestPathTestCase {
	const char *name;
	int source;
	vector<vector<WeightedEdge>> graph;
	vector<vector<ll>> ans;
	bool has_negative_cycle;
};

inline vector<ShortestPathTestCase> non_neg_weight_graph_cases() {
	return {
		{"simple",
		 0,
		 {{{1, 1}, {2, 4}}, {{2, 2}}, {}},
		 {{0, 1, 3}, {inf, 0, 2}, {inf, inf, 0}},
		 false},
		{"disconnected",
		 0,
		 {{{1, 5}}, {}, {}, {}},
		 {{0, 5, inf, inf},
		  {inf, 0, inf, inf},
		  {inf, inf, 0, inf},
		  {inf, inf, inf, 0}},
		 false},
		{"multiple_paths",
		 0,
		 {{{1, 1}, {2, 2}}, {{3, 4}}, {{3, 1}}, {}},
		 {{0, 1, 2, 3}, {inf, 0, inf, 4}, {inf, inf, 0, 1}, {inf, inf, inf, 0}},
		 false},
	};
}

inline vector<ShortestPathTestCase> with_neg_weight_graph_cases() {
	return {
		{"neg_weight_no_cycle",
		 0,
		 {{{1, 2}, {2, 5}}, {{2, -1}}, {{0, 4}}},
		 {{0, 2, 1}, {3, 0, -1}, {4, 6, 0}},
		 false},
		{"neg_cycle", 0, {{{1, 1}}, {{2, -3}}, {{1, 1}}}, {}, true},
	};
}
