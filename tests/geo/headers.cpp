#include "geo/fp/andrew.h"
#include "geo/fp/apollo.h"
#include "geo/fp/convex.h"
#include "geo/fp/cover.h"
#include "geo/fp/halfinter.h"
#include "geo/fp/interarea.h"
#include "geo/fp/inverse.h"
#include "geo/fp/kdtree.h"
#include "geo/fp/nearest.h"
#include "geo/fp/scanline.h"
#include "geo/int/lichao.h"
#include "geo/int/pick.h"
#include "doctest.h"

TEST_CASE("integer_and_floating_geometry_can_coexist") {
	Point fp(1.5l, 2.5l);
	PointInt integer(1, 2);
	REQUIRE(cmp(fp.x, 1.5l) == 0);
	REQUIRE(integer.x == 1);

	Line fp_line(Point(), fp);
	LineInt integer_line(PointInt(), integer);
	REQUIRE(is_on(Point(), fp_line));
	REQUIRE(is_on(PointInt(), integer_line));
}
