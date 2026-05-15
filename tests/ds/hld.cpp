#include "ds/hld.h"
#include "../test.h"

TEST(hld_path_and_subtree_ranges) {
	vector<vector<int>> edges = {{1, 2}, {0, 3, 4}, {0}, {1}, {1}};
	HLD hld(edges);

	ENSURE(hld.lca(3, 4) == 1);
	ENSURE(hld.lca(2, 4) == 0);
	ENSURE(hld.dep[4] == 2);
	ENSURE(hld.fa[4] == 1);
	ENSURE(hld.toc[3] == hld.toc[1]);
	ENSURE(hld.size(1) == 3);

	vector<pair<int, int>> path_3_2 = hld.query_path(3, 2);
	ENSURE(path_3_2.size() == 2);
	ENSURE((path_3_2[0] == std::pair<int, int>{0, 3}));
	ENSURE((path_3_2[1] == std::pair<int, int>{4, 5}));

	vector<pair<int, int>> path_3_4 = hld.query_path(3, 4);
	ENSURE(path_3_4.size() == 2);
	ENSURE((path_3_4[0] == std::pair<int, int>{1, 3}));
	ENSURE((path_3_4[1] == std::pair<int, int>{3, 4}));

	ENSURE((hld.query_subtree(1) == std::pair<int, int>{1, 4}));
}
