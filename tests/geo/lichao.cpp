#include "geo/lichao.h"
#include "../test.h"

TEST(tie_break_prefers_smaller_id) {
	LiChao t(2);
	t.addline(1, 0, -2, 1);
	t.addline(1, 0, -2, 3);

	ENSURE(t.query(0) == 1);
	ENSURE(t.query(1) == 0);
}

TEST(distinguishes_large_values_with_subunit_gap) {
	LiChao t(40000);
	t.addline(1, 39989, 999999999, 1000000000);
	t.addline(1, 39989, 1000000000, 1000000000);

	ENSURE(t.query(19995) == 1);
}
