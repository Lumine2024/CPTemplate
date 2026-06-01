#include "graph/prim.h"
#include "mst_test_cases.h"
#include "doctest.h"

static vector<vector<WeightedEdge>> to_graph(const MstCase &tc) {
	vector<vector<WeightedEdge>> g(tc.n);
	for(const auto &e : tc.edges) {
		g[e.u].push_back({e.v, e.w});
		g[e.v].push_back({e.u, e.w});
	}
	return g;
}

TEST_CASE("prim_shared_mst_cases") {
	for(const auto &tc : mst_cases()) {
		auto g = to_graph(tc);
		REQUIRE(prim(g) == tc.expected);
	}
}
