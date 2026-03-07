#include "twosat.h"
#include "../test.h"

// Each condition (i, fi, j, fj) means: (x_i == fi) OR (x_j == fj)
TEST(twosat_satisfiable) {
	// Simple: x0=1 OR x1=0, always satisfiable
	vector<tuple<int, int, int, int>> conds = {{0, 1, 1, 0}};
	auto ans = twosat(2, conds);
	ENSURE(!ans.empty());
	// Verify: x0==ans[0], check condition
	bool ok = (ans[0] == 1) || (ans[1] == 0);
	ENSURE(ok);
}

TEST(twosat_unsatisfiable) {
	// x0=1 OR x0=1, x0=0 OR x0=0: contradiction if x0 must be both 0 and 1
	// Force x0=1: (x0=1 OR x0=1)
	// Force x0=0: (x0=0 OR x0=0)
	// Together: x0 must be both 1 and 0 -> unsatisfiable
	vector<tuple<int, int, int, int>> conds = {{0, 1, 0, 1}, {0, 0, 0, 0}};
	auto ans = twosat(1, conds);
	ENSURE(ans.empty());
}

TEST(twosat_two_vars) {
	// x0=1 OR x1=1, x0=0 OR x1=0
	// = at least one is 1, at least one is 0
	// Satisfiable: x0=1, x1=0 or x0=0, x1=1
	vector<tuple<int, int, int, int>> conds = {{0, 1, 1, 1}, {0, 0, 1, 0}};
	auto ans = twosat(2, conds);
	ENSURE(!ans.empty());
	bool c1 = (ans[0] == 1) || (ans[1] == 1);
	bool c2 = (ans[0] == 0) || (ans[1] == 0);
	ENSURE(c1 && c2);
}

TEST(twosat_all_same) {
	// x0=0 OR x0=0, x1=0 OR x1=0: forces x0=0, x1=0
	vector<tuple<int, int, int, int>> conds = {{0, 0, 0, 0}, {1, 0, 1, 0}};
	auto ans = twosat(2, conds);
	ENSURE(!ans.empty());
	ENSURE(ans[0] == 0);
	ENSURE(ans[1] == 0);
}
