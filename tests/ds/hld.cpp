#include "ds/hld.h"
#include "../test.h"

struct SumInfo {
	int sum;
	SumInfo(int v = 0) : sum(v) {}
	SumInfo operator+(const SumInfo &other) const {
		return SumInfo(sum + other.sum);
	}
	void apply(SumInfo &dst) const {
		dst = *this;
	}
};

struct AssignInfo {
	int value;
	void apply(SumInfo &dst) const {
		dst.sum = value;
	}
};

TEST(hld_path_subtree_and_modify) {
	vector<vector<int>> edges = {{1, 2}, {0, 3, 4}, {0}, {1}, {1}};
	vector<SumInfo> weights = {1, 2, 3, 4, 5};
	HLD<SumInfo, AssignInfo> hld(edges, weights);

	ENSURE(hld.lca(3, 4) == 1);
	ENSURE(hld.lca(2, 4) == 0);
	ENSURE(hld.query_path(3, 2).sum == 10);
	ENSURE(hld.query_subtree(1).sum == 11);

	hld.modify(4, AssignInfo{8});
	ENSURE(hld.query_path(3, 4).sum == 14);
	ENSURE(hld.query_subtree(1).sum == 14);
	ENSURE(hld.size(1) == 3);
}
