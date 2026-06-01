#include "geo/lichao.h"
#include "doctest.h"

TEST_CASE("tie_break_prefers_smaller_id") {
	LiChao t(2);
	t.addline(1, 0, -2, 1);
	t.addline(1, 0, -2, 3);

	REQUIRE(t.query(0) == 1);
	REQUIRE(t.query(1) == 0);
}

TEST_CASE("distinguishes_large_values_with_subunit_gap") {
	LiChao t(40000);
	t.addline(1, 39989, 999999999, 1000000000);
	t.addline(1, 39989, 1000000000, 1000000000);

	REQUIRE(t.query(19995) == 1);
}
