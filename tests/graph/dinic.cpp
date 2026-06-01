#include "graph/dinic.h"
#include "doctest.h"

TEST_CASE("dinic_simple") {
	// s=0, t=3, path 0->1->3 (cap 3), path 0->2->3 (cap 2)
	Dinic d(4, 0, 3);
	d.addedge(0, 1, 3);
	d.addedge(0, 2, 2);
	d.addedge(1, 3, 3);
	d.addedge(2, 3, 2);
	REQUIRE(d.maxflow() == 5);
}

TEST_CASE("dinic_bottleneck") {
	// s=0, t=2: 0->1 (cap 10), 1->2 (cap 3)
	Dinic d(3, 0, 2);
	d.addedge(0, 1, 10);
	d.addedge(1, 2, 3);
	REQUIRE(d.maxflow() == 3);
}

TEST_CASE("dinic_no_path") {
	// No edges at all
	Dinic d(2, 0, 1);
	REQUIRE(d.maxflow() == 0);
}

TEST_CASE("dinic_parallel_edges") {
	// 0->1: two edges of cap 5 and 3
	Dinic d(2, 0, 1);
	d.addedge(0, 1, 5);
	d.addedge(0, 1, 3);
	REQUIRE(d.maxflow() == 8);
}

TEST_CASE("dinic_grid") {
	// 0->1 (5), 0->2 (4), 1->2 (2), 1->3 (8), 2->3 (6)
	Dinic d(4, 0, 3);
	d.addedge(0, 1, 5);
	d.addedge(0, 2, 4);
	d.addedge(1, 2, 2);
	d.addedge(1, 3, 8);
	d.addedge(2, 3, 6);
	// max flow: min cut analysis
	// Path 0->1->3: 5, Path 0->2->3: 4, Path 0->1->2->3: 1 more via 1->2 after
	// 5 used
	REQUIRE(d.maxflow() == 9);
}
