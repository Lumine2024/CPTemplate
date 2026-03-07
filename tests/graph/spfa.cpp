#include "spfa.h"
#include "../test.h"

TEST(spfa_simple) {
	vector<vector<pair<int, ll>>> g(3);
	g[0].push_back({1, 1});
	g[0].push_back({2, 4});
	g[1].push_back({2, 2});
	auto dist = spfa(g, 0);
	ENSURE(!dist.empty());
	ENSURE(dist[0] == 0);
	ENSURE(dist[1] == 1);
	ENSURE(dist[2] == 3);
}

TEST(spfa_negative_weights) {
	// 0 -> 1 (w=2), 1 -> 2 (w=-1), 0 -> 2 (w=5)
	vector<vector<pair<int, ll>>> g(3);
	g[0].push_back({1, 2});
	g[1].push_back({2, -1});
	g[0].push_back({2, 5});
	auto dist = spfa(g, 0);
	ENSURE(!dist.empty());
	ENSURE(dist[0] == 0);
	ENSURE(dist[1] == 2);
	ENSURE(dist[2] == 1);
}

TEST(spfa_negative_cycle) {
	// 0->1 (w=1), 1->2 (w=-3), 2->1 (w=1): negative cycle
	vector<vector<pair<int, ll>>> g(3);
	g[0].push_back({1, 1});
	g[1].push_back({2, -3});
	g[2].push_back({1, 1});
	auto dist = spfa(g, 0);
	ENSURE(dist.empty());  // negative cycle detected
}

TEST(spfa_disconnected) {
	vector<vector<pair<int, ll>>> g(4);
	g[0].push_back({1, 3});
	auto dist = spfa(g, 0);
	ENSURE(!dist.empty());
	ENSURE(dist[0] == 0);
	ENSURE(dist[1] == 3);
	ENSURE(dist[2] == inf);
	ENSURE(dist[3] == inf);
}
