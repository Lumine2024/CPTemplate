#include "dijk.h"
#include "../test.h"

TEST(dijkstra_simple) {
	// 0 -> 1 (weight 1), 0 -> 2 (weight 4), 1 -> 2 (weight 2)
	vector<vector<pair<int, ll>>> g(3);
	g[0].push_back({1, 1});
	g[0].push_back({2, 4});
	g[1].push_back({2, 2});
	auto dist = dijkstra(g, 0);
	ENSURE(dist[0] == 0);
	ENSURE(dist[1] == 1);
	ENSURE(dist[2] == 3);
}

TEST(dijkstra_disconnected) {
	vector<vector<pair<int, ll>>> g(4);
	g[0].push_back({1, 5});
	// node 2 and 3 are disconnected from 0
	auto dist = dijkstra(g, 0);
	ENSURE(dist[0] == 0);
	ENSURE(dist[1] == 5);
	ENSURE(dist[2] == inf);
	ENSURE(dist[3] == inf);
}

TEST(dijkstra_single_node) {
	vector<vector<pair<int, ll>>> g(1);
	auto dist = dijkstra(g, 0);
	ENSURE(dist[0] == 0);
}

TEST(dijkstra_chain) {
	// Chain: 0 -1-> 1 -2-> 2 -3-> 3 -4-> 4
	int n = 5;
	vector<vector<pair<int, ll>>> g(n);
	for(int i = 0; i < n - 1; ++i) g[i].push_back({i + 1, i + 1});
	auto dist = dijkstra(g, 0);
	ENSURE(dist[0] == 0);
	ENSURE(dist[1] == 1);
	ENSURE(dist[2] == 3);
	ENSURE(dist[3] == 6);
	ENSURE(dist[4] == 10);
}

TEST(dijkstra_multiple_paths) {
	// Diamond: 0->1 (w=1), 0->2 (w=2), 1->3 (w=4), 2->3 (w=1)
	vector<vector<pair<int, ll>>> g(4);
	g[0].push_back({1, 1});
	g[0].push_back({2, 2});
	g[1].push_back({3, 4});
	g[2].push_back({3, 1});
	auto dist = dijkstra(g, 0);
	ENSURE(dist[0] == 0);
	ENSURE(dist[1] == 1);
	ENSURE(dist[2] == 2);
	ENSURE(dist[3] == 3);  // 0->2->3: 2+1=3
}
