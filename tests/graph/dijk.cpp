#include "graph/dijk.h"
#include "shortest_path_cases.h"
#include "doctest.h"

TEST_CASE("dijkstra_shared_shortest_path_cases") {
	for(const auto &tc : non_neg_weight_graph_cases()) {
		auto dist = dijkstra(tc.graph, tc.source);
		REQUIRE(dist == tc.ans[tc.source]);
	}
}
