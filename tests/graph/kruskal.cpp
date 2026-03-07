#include "kruskal.h"
#include "../test.h"

TEST(kruskal_simple_triangle) {
	// Triangle: 0-1 (w=1), 1-2 (w=2), 0-2 (w=3)
	// MST: edges (0,1,1) + (1,2,2) = 3
	vector<Edge> edges = {{0, 1, 1}, {1, 2, 2}, {0, 2, 3}};
	ENSURE(kruskal(edges, 3) == 3);
}

TEST(kruskal_disconnected) {
	// Two disconnected components: 0-1 and 2-3
	vector<Edge> edges = {{0, 1, 5}, {2, 3, 7}};
	ENSURE(kruskal(edges, 4) == inf);  // disconnected
}

TEST(kruskal_single_node) {
	vector<Edge> edges;
	ENSURE(kruskal(edges, 1) == 0);
}

TEST(kruskal_square_with_diagonal) {
	// Square 0-1-2-3-0 with diagonal 0-2
	// Edges: (0,1,1),(1,2,2),(2,3,3),(3,0,4),(0,2,5)
	// MST: (0,1,1)+(1,2,2)+(2,3,3) = 6
	vector<Edge> edges = {
		{0, 1, 1}, {1, 2, 2}, {2, 3, 3}, {3, 0, 4}, {0, 2, 5}};
	ENSURE(kruskal(edges, 4) == 6);
}

TEST(kruskal_complete_graph) {
	// K4 with varying weights
	// All edges: (0,1,10),(0,2,6),(0,3,5),(1,2,15),(1,3,4),(2,3,12)
	// MST: (1,3,4)+(0,3,5)+(0,2,6) = 15
	vector<Edge> edges = {{0, 1, 10}, {0, 2, 6}, {0, 3, 5},
	                      {1, 2, 15}, {1, 3, 4}, {2, 3, 12}};
	ENSURE(kruskal(edges, 4) == 15);
}
