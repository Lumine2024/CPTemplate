#include "ds/binlift.h"
#include "doctest.h"

TEST_CASE("binlift_lca_simple_chain") {
	// Chain: 0 - 1 - 2 - 3 - 4
	BinaryLift bl(5);
	bl.add_edge(0, 1);
	bl.add_edge(1, 2);
	bl.add_edge(2, 3);
	bl.add_edge(3, 4);
	bl.build(0);
	REQUIRE(bl.lca(0, 4) == 0);
	REQUIRE(bl.lca(1, 3) == 1);
	REQUIRE(bl.lca(2, 4) == 2);
	REQUIRE(bl.lca(3, 4) == 3);
	REQUIRE(bl.lca(2, 2) == 2);
}

TEST_CASE("binlift_lca_star") {
	// Star: center 0, leaves 1..4
	BinaryLift bl(5);
	for(int i = 1; i <= 4; ++i) bl.add_edge(0, i);
	bl.build(0);
	REQUIRE(bl.lca(1, 2) == 0);
	REQUIRE(bl.lca(3, 4) == 0);
	REQUIRE(bl.lca(0, 3) == 0);
	REQUIRE(bl.lca(1, 1) == 1);
}

TEST_CASE("binlift_lca_balanced_tree") {
	// Binary tree rooted at 0
	//        0
	//      1   2
	//    3   4 5  6
	BinaryLift bl(7);
	bl.add_edge(0, 1);
	bl.add_edge(0, 2);
	bl.add_edge(1, 3);
	bl.add_edge(1, 4);
	bl.add_edge(2, 5);
	bl.add_edge(2, 6);
	bl.build(0);
	REQUIRE(bl.lca(3, 4) == 1);
	REQUIRE(bl.lca(5, 6) == 2);
	REQUIRE(bl.lca(3, 5) == 0);
	REQUIRE(bl.lca(4, 6) == 0);
	REQUIRE(bl.lca(3, 1) == 1);
}

TEST_CASE("binlift_kth_ancestor") {
	// Chain: 0 - 1 - 2 - 3 - 4
	BinaryLift bl(5);
	bl.add_edge(0, 1);
	bl.add_edge(1, 2);
	bl.add_edge(2, 3);
	bl.add_edge(3, 4);
	bl.build(0);
	REQUIRE(bl.kth_ancestor(4, 1) == 3);
	REQUIRE(bl.kth_ancestor(4, 2) == 2);
	REQUIRE(bl.kth_ancestor(4, 4) == 0);
	REQUIRE(bl.kth_ancestor(4, 5) == -1);
	REQUIRE(bl.kth_ancestor(0, 0) == 0);
}
