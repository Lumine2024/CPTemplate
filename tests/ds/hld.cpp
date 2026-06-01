#include "ds/hld.h"
#include "doctest.h"

TEST_CASE("hld_path_and_subtree_ranges") {
	vector<vector<int>> edges = {{1, 2}, {0, 3, 4}, {0}, {1}, {1}};
	HLD hld(edges);

	REQUIRE(hld.lca(3, 4) == 1);
	REQUIRE(hld.lca(2, 4) == 0);
	REQUIRE(hld.dep[4] == 2);
	REQUIRE(hld.fa[4] == 1);
	REQUIRE(hld.toc[3] == hld.toc[1]);
	REQUIRE(hld.size(1) == 3);

	vector<pair<int, int>> path_3_2 = hld.query_path(3, 2);
	REQUIRE(path_3_2.size() == 2);
	REQUIRE((path_3_2[0] == std::pair<int, int>{0, 3}));
	REQUIRE((path_3_2[1] == std::pair<int, int>{4, 5}));

	vector<pair<int, int>> path_3_4 = hld.query_path(3, 4);
	REQUIRE(path_3_4.size() == 2);
	REQUIRE((path_3_4[0] == std::pair<int, int>{1, 3}));
	REQUIRE((path_3_4[1] == std::pair<int, int>{3, 4}));

	REQUIRE((hld.query_subtree(1) == std::pair<int, int>{1, 4}));
}
