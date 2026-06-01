#include "graph/spfa.h"
#include "shortest_path_cases.h"
#include "doctest.h"

TEST_CASE("spfa_shared_shortest_path_cases") {
	for(const auto &tc : non_neg_weight_graph_cases()) {
		auto dist = spfa(tc.graph, tc.source);
		REQUIRE(!dist.empty());
		REQUIRE(dist == tc.ans[tc.source]);
	}
	for(const auto &tc : with_neg_weight_graph_cases()) {
		auto dist = spfa(tc.graph, tc.source);
		if(tc.has_negative_cycle) {
			REQUIRE(dist.empty());
		} else {
			REQUIRE(!dist.empty());
			REQUIRE(dist == tc.ans[tc.source]);
		}
	}
}
