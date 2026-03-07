#include "binlift.h"
#include "../test.h"

TEST(binlift_lca_simple_chain) {
	// Chain: 0 - 1 - 2 - 3 - 4
	BinaryLift bl(5);
	bl.addedge(0, 1);
	bl.addedge(1, 2);
	bl.addedge(2, 3);
	bl.addedge(3, 4);
	bl.build(0);
	ENSURE(bl.lca(0, 4) == 0);
	ENSURE(bl.lca(1, 3) == 1);
	ENSURE(bl.lca(2, 4) == 2);
	ENSURE(bl.lca(3, 4) == 3);
	ENSURE(bl.lca(2, 2) == 2);
}

TEST(binlift_lca_star) {
	// Star: center 0, leaves 1..4
	BinaryLift bl(5);
	for(int i = 1; i <= 4; ++i) bl.addedge(0, i);
	bl.build(0);
	ENSURE(bl.lca(1, 2) == 0);
	ENSURE(bl.lca(3, 4) == 0);
	ENSURE(bl.lca(0, 3) == 0);
	ENSURE(bl.lca(1, 1) == 1);
}

TEST(binlift_lca_balanced_tree) {
	// Binary tree rooted at 0
	//        0
	//      1   2
	//    3   4 5  6
	BinaryLift bl(7);
	bl.addedge(0, 1);
	bl.addedge(0, 2);
	bl.addedge(1, 3);
	bl.addedge(1, 4);
	bl.addedge(2, 5);
	bl.addedge(2, 6);
	bl.build(0);
	ENSURE(bl.lca(3, 4) == 1);
	ENSURE(bl.lca(5, 6) == 2);
	ENSURE(bl.lca(3, 5) == 0);
	ENSURE(bl.lca(4, 6) == 0);
	ENSURE(bl.lca(3, 1) == 1);
}

TEST(binlift_kth_ancestor) {
	// Chain: 0 - 1 - 2 - 3 - 4
	BinaryLift bl(5);
	bl.addedge(0, 1);
	bl.addedge(1, 2);
	bl.addedge(2, 3);
	bl.addedge(3, 4);
	bl.build(0);
	ENSURE(bl.kth_ancestor(4, 1) == 3);
	ENSURE(bl.kth_ancestor(4, 2) == 2);
	ENSURE(bl.kth_ancestor(4, 4) == 0);
	ENSURE(bl.kth_ancestor(4, 5) == -1);
	ENSURE(bl.kth_ancestor(0, 0) == 0);
}
