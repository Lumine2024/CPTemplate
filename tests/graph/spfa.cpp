#include "spfa.h"
#include "shortest_path_cases.h"
#include "../test.h"

TEST(spfa_shared_shortest_path_cases) {
	for(const auto &tc : non_neg_weight_graph_cases()) {
		auto dist = spfa(tc.graph, tc.source);
		ENSURE(!dist.empty());
		ENSURE(dist == tc.ans[tc.source]);
	}
	for(const auto &tc : with_neg_weight_graph_cases()) {
		auto dist = spfa(tc.graph, tc.source);
		if(tc.has_negative_cycle) {
			ENSURE(dist.empty());
		} else {
			ENSURE(!dist.empty());
			ENSURE(dist == tc.ans[tc.source]);
		}
	}
}
