#include "graph/tarjan.h"
#include "doctest.h"

TEST_CASE("scc_single_node") {
	SCC scc(1);
	scc.build();
	REQUIRE(scc.sccs.size() == 1);
	REQUIRE(scc.inscc[0] == 0);
}

TEST_CASE("scc_simple_cycle") {
	// 0->1->2->0: one SCC of size 3
	SCC scc(3);
	scc.addedge(0, 1);
	scc.addedge(1, 2);
	scc.addedge(2, 0);
	scc.build();
	REQUIRE(scc.sccs.size() == 1);
	REQUIRE(scc.inscc[0] == scc.inscc[1]);
	REQUIRE(scc.inscc[1] == scc.inscc[2]);
}

TEST_CASE("scc_two_separate_components") {
	// 0->1->0 and 2->3->2
	SCC scc(4);
	scc.addedge(0, 1);
	scc.addedge(1, 0);
	scc.addedge(2, 3);
	scc.addedge(3, 2);
	scc.build();
	REQUIRE(scc.sccs.size() == 2);
	REQUIRE(scc.inscc[0] == scc.inscc[1]);
	REQUIRE(scc.inscc[2] == scc.inscc[3]);
	REQUIRE(scc.inscc[0] != scc.inscc[2]);
}

TEST_CASE("scc_dag") {
	// 0->1->2->3, no back edges: 4 SCCs
	SCC scc(4);
	scc.addedge(0, 1);
	scc.addedge(1, 2);
	scc.addedge(2, 3);
	scc.build();
	REQUIRE(scc.sccs.size() == 4);
	for(int i = 0; i < 4; ++i) {
		for(int j = i + 1; j < 4; ++j) {
			REQUIRE(scc.inscc[i] != scc.inscc[j]);
		}
	}
}

TEST_CASE("scc_condensation_dag") {
	// 0->1->2->0 (SCC), 2->3->4 (dag)
	SCC scc(5);
	scc.addedge(0, 1);
	scc.addedge(1, 2);
	scc.addedge(2, 0);
	scc.addedge(2, 3);
	scc.addedge(3, 4);
	scc.build();
	REQUIRE(scc.sccs.size() == 3);
	// nodes 0,1,2 in same SCC
	REQUIRE(scc.inscc[0] == scc.inscc[1]);
	REQUIRE(scc.inscc[1] == scc.inscc[2]);
	// nodes 3 and 4 are separate
	REQUIRE(scc.inscc[3] != scc.inscc[4]);
	REQUIRE(scc.inscc[0] != scc.inscc[3]);
}

TEST_CASE("bridge_simple") {
	// 0-1-2, edge 1-2 is a bridge
	Bridge br(3);
	br.addedge(0, 1);
	br.addedge(1, 2);
	br.build();
	REQUIRE(br.bridges.size() == 2);
}

TEST_CASE("bridge_cycle_no_bridge") {
	// Triangle: 0-1-2-0, no bridges
	Bridge br(3);
	br.addedge(0, 1);
	br.addedge(1, 2);
	br.addedge(2, 0);
	br.build();
	REQUIRE(br.bridges.empty());
}

TEST_CASE("ap_simple") {
	// 0-1-2, node 1 is an articulation point
	AP ap(3);
	ap.addedge(0, 1);
	ap.addedge(1, 2);
	ap.build();
	REQUIRE(ap.ap.size() == 1);
	REQUIRE(ap.ap[0] == 1);
}

TEST_CASE("ap_cycle_no_cutpoint") {
	// Triangle: no articulation points
	AP ap(3);
	ap.addedge(0, 1);
	ap.addedge(1, 2);
	ap.addedge(2, 0);
	ap.build();
	REQUIRE(ap.ap.empty());
}
