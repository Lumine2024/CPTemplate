#include "geo/halfinter.h"
#include "../test.h"

static void ensure_point_eq(const Point &a, const Point &b) {
	ENSURE(cmp(a.x, b.x) == 0);
	ENSURE(cmp(a.y, b.y) == 0);
}

TEST(halfinter_unit_square) {
	// Four half-planes forming the unit square [0,1]x[0,1]
	// y >= 0: Line((0,0), dir(1,0))
	// x <= 1: Line((1,0), dir(0,1))
	// y <= 1: Line((1,1), dir(-1,0))
	// x >= 0: Line((0,1), dir(0,-1))
	vector<Line> lines = {
		Line(Point(0.0l, 0.0l), Vector(1.0l, 0.0l)),
		Line(Point(1.0l, 0.0l), Vector(0.0l, 1.0l)),
		Line(Point(1.0l, 1.0l), Vector(-1.0l, 0.0l)),
		Line(Point(0.0l, 1.0l), Vector(0.0l, -1.0l)),
	};
	auto result = half_inter(lines);
	ENSURE(result.size() >= 3);
	Polygon poly(result);
	ENSURE(cmp(abs(poly.area()), 1.0l) == 0);
}

TEST(halfinter_right_triangle) {
	// Three half-planes: x >= 0, y >= 0, x + y <= 2
	// Forms a right triangle with area 2
	// x >= 0: Line((0,1), dir(0,-1)) → cross((0,-1),(x,y-1)) = x >= 0
	// y >= 0: Line((0,0), dir(1,0))
	// x+y <= 2: Line((2,0), dir(-1,1)) → cross((-1,1),(x-2,y)) = -(x-2)-(-1)*y = 2-x+y? Wait
	// Let me verify: cross((-1,1),(x-2,y)) = (-1)*y - 1*(x-2) = -y - x + 2 = 2-x-y >= 0 → x+y <= 2 ✓
	vector<Line> lines = {
		Line(Point(0.0l, 1.0l), Vector(0.0l, -1.0l)),
		Line(Point(0.0l, 0.0l), Vector(1.0l, 0.0l)),
		Line(Point(2.0l, 0.0l), Vector(-1.0l, 1.0l)),
	};
	auto result = half_inter(lines);
	ENSURE(result.size() >= 3);
	Polygon poly(result);
	ENSURE(cmp(abs(poly.area()), 2.0l) == 0);
}

TEST(halfinter_empty) {
	// Two contradictory half-planes: x >= 1 and x <= 0
	// x >= 1: Line((1,0), dir(0,1)) → cross((0,1),(x-1,y)) = -(x-1) = 1-x? No.
	// cross((0,1),(x-1,y)) = 0*y - 1*(x-1) = -(x-1) = 1-x >= 0 → x <= 1
	// x >= 2: Line((2,0), dir(0,-1)) → cross((0,-1),(x-2,y)) = x-2 >= 0 → x >= 2
	// These are contradictory (x <= 1 AND x >= 2)
	vector<Line> lines = {
		Line(Point(1.0l, 0.0l), Vector(0.0l, 1.0l)),  // x <= 1
		Line(Point(2.0l, 0.0l), Vector(0.0l, -1.0l)), // x >= 2
	};
	auto result = half_inter(lines);
	ENSURE(result.size() == 0);
}
