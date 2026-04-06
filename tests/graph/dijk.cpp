#include "graph/dijk.h"
#include "shortest_path_cases.h"
#include "../test.h"

TEST(dijkstra_shared_shortest_path_cases) {
	for(const auto &tc : non_neg_weight_graph_cases()) {
		auto dist = dijkstra(tc.graph, tc.source);
		ENSURE(dist == tc.ans[tc.source]);
	}
}
