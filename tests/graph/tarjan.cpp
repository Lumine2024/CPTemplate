#include "tarjan.h"
#include "../test.h"

TEST(scc_single_node) {
	SCC scc(1);
	scc.build();
	ENSURE(scc.sccs.size() == 1);
	ENSURE(scc.nodes[0].inscc == 0);
}

TEST(scc_simple_cycle) {
	// 0->1->2->0: one SCC of size 3
	SCC scc(3);
	scc.addedge(0, 1);
	scc.addedge(1, 2);
	scc.addedge(2, 0);
	scc.build();
	ENSURE(scc.sccs.size() == 1);
	ENSURE(scc.nodes[0].inscc == scc.nodes[1].inscc);
	ENSURE(scc.nodes[1].inscc == scc.nodes[2].inscc);
}

TEST(scc_two_separate_components) {
	// 0->1->0 and 2->3->2
	SCC scc(4);
	scc.addedge(0, 1);
	scc.addedge(1, 0);
	scc.addedge(2, 3);
	scc.addedge(3, 2);
	scc.build();
	ENSURE(scc.sccs.size() == 2);
	ENSURE(scc.nodes[0].inscc == scc.nodes[1].inscc);
	ENSURE(scc.nodes[2].inscc == scc.nodes[3].inscc);
	ENSURE(scc.nodes[0].inscc != scc.nodes[2].inscc);
}

TEST(scc_dag) {
	// 0->1->2->3, no back edges: 4 SCCs
	SCC scc(4);
	scc.addedge(0, 1);
	scc.addedge(1, 2);
	scc.addedge(2, 3);
	scc.build();
	ENSURE(scc.sccs.size() == 4);
	for(int i = 0; i < 4; ++i) {
		for(int j = i + 1; j < 4; ++j) {
			ENSURE(scc.nodes[i].inscc != scc.nodes[j].inscc);
		}
	}
}

TEST(scc_condensation_dag) {
	// 0->1->2->0 (SCC), 2->3->4 (dag)
	SCC scc(5);
	scc.addedge(0, 1);
	scc.addedge(1, 2);
	scc.addedge(2, 0);
	scc.addedge(2, 3);
	scc.addedge(3, 4);
	scc.build();
	ENSURE(scc.sccs.size() == 3);
	// nodes 0,1,2 in same SCC
	ENSURE(scc.nodes[0].inscc == scc.nodes[1].inscc);
	ENSURE(scc.nodes[1].inscc == scc.nodes[2].inscc);
	// nodes 3 and 4 are separate
	ENSURE(scc.nodes[3].inscc != scc.nodes[4].inscc);
	ENSURE(scc.nodes[0].inscc != scc.nodes[3].inscc);
}

TEST(bridge_simple) {
	// 0-1-2, edge 1-2 is a bridge
	Bridge br(3);
	br.addedge(0, 1);
	br.addedge(1, 2);
	br.build();
	ENSURE(br.bridges.size() == 2);
}

TEST(bridge_cycle_no_bridge) {
	// Triangle: 0-1-2-0, no bridges
	Bridge br(3);
	br.addedge(0, 1);
	br.addedge(1, 2);
	br.addedge(2, 0);
	br.build();
	ENSURE(br.bridges.empty());
}

TEST(ap_simple) {
	// 0-1-2, node 1 is an articulation point
	AP ap(3);
	ap.addedge(0, 1);
	ap.addedge(1, 2);
	ap.build();
	ENSURE(ap.cutpoints.size() == 1);
	ENSURE(ap.cutpoints[0] == 1);
}

TEST(ap_cycle_no_cutpoint) {
	// Triangle: no articulation points
	AP ap(3);
	ap.addedge(0, 1);
	ap.addedge(1, 2);
	ap.addedge(2, 0);
	ap.build();
	ENSURE(ap.cutpoints.empty());
}
