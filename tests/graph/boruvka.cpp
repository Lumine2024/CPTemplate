#include "graph/boruvka.h"
#include "mst_test_cases.h"
#include "doctest.h"

TEST_CASE("boruvka_shared_mst_cases") {
	for(const auto &tc : mst_cases()) {
		vector<Edge> edges;
		edges.reserve(tc.edges.size());
		for(const auto &e : tc.edges) {
			edges.push_back({e.u, e.v, e.w});
		}
		REQUIRE(boruvka(edges, tc.n) == tc.expected);
	}
}
