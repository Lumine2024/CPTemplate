#include "graph/mcmf.h"
#include "doctest.h"

TEST_CASE("mcmf_simple") {
	MCMF graph(2);
	graph.add_edge(0, 1, 2, 3);
	auto [mc, mf] = graph.mcmf(0, 1);
	REQUIRE(mc == 6);
	REQUIRE(mf == 2);
}

TEST_CASE("mcmf_negative_weight") {
	MCMF graph(4);
	graph.add_edge(3, 0, 1, 0);
	graph.add_edge(0, 1, 1, 1);
	graph.add_edge(0, 2, 1, 5);
	graph.add_edge(2, 1, 1, -10);
	auto [mc, mf] = graph.mcmf(3, 1);
	REQUIRE(mc == -5);
	REQUIRE(mf == 1);
}
