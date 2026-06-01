#include "geo/andrew.h"
#include "doctest.h"

static void ensure_point_eq(const Point &a, const Point &b) {
	REQUIRE(cmp(a.x, b.x) == 0);
	REQUIRE(cmp(a.y, b.y) == 0);
}

static bool contains_point(const vector<Point> &pts, const Point &p) {
	for(const auto &x : pts) {
		if(x == p) return true;
	}
	return false;
}

TEST_CASE("simple_convex") {
	vector<Point> points = {
		{0.0l, 0.0l}, {1.0l, 0.0l}, {1.0l, 1.0l}, {0.0l, 1.0l}};
	auto convex = andrew(points);
	REQUIRE(convex.size() == 4);
	ensure_point_eq(convex[0], Point(0.0l, 0.0l));
	ensure_point_eq(convex[1], Point(1.0l, 0.0l));
	ensure_point_eq(convex[2], Point(1.0l, 1.0l));
	ensure_point_eq(convex[3], Point(0.0l, 1.0l));
}

TEST_CASE("degenerate_cases") {
	vector<Point> one = {{2.0l, -3.0l}};
	auto hull_one = andrew(one);
	REQUIRE(hull_one.size() == 1);
	ensure_point_eq(hull_one[0], Point(2.0l, -3.0l));

	vector<Point> two = {{5.0l, 1.0l}, {-1.0l, 4.0l}};
	auto hull_two = andrew(two);
	REQUIRE(hull_two.size() == 2);
	ensure_point_eq(hull_two[0], Point(-1.0l, 4.0l));
	ensure_point_eq(hull_two[1], Point(5.0l, 1.0l));

	vector<Point> all_same = {
		{1.5l, 1.5l}, {1.5l, 1.5l}, {1.5l, 1.5l}, {1.5l, 1.5l}};
	auto hull_same = andrew(all_same);
	REQUIRE(hull_same.size() == 1);
	ensure_point_eq(hull_same[0], Point(1.5l, 1.5l));
}

TEST_CASE("collinear_points") {
	vector<Point> points = {{-3.0l, 0.0l}, {0.0l, 0.0l}, {2.0l, 0.0l},
							{5.0l, 0.0l},  {2.0l, 0.0l}, {-1.0l, 0.0l}};
	auto hull = andrew(points);
	REQUIRE(hull.size() == 2);
	ensure_point_eq(hull[0], Point(-3.0l, 0.0l));
	ensure_point_eq(hull[1], Point(5.0l, 0.0l));
}

TEST_CASE("duplicates_and_interior_points") {
	vector<Point> points = {{0.0l, 0.0l}, {4.0l, 0.0l}, {4.0l, 4.0l},
							{0.0l, 4.0l}, {2.0l, 2.0l}, {1.0l, 1.0l},
							{3.0l, 1.0l}, {0.0l, 0.0l}, {4.0l, 0.0l}};
	auto hull = andrew(points);
	REQUIRE(hull.size() == 4);
	REQUIRE(contains_point(hull, Point(0.0l, 0.0l)));
	REQUIRE(contains_point(hull, Point(4.0l, 0.0l)));
	REQUIRE(contains_point(hull, Point(4.0l, 4.0l)));
	REQUIRE(contains_point(hull, Point(0.0l, 4.0l)));
	REQUIRE(!contains_point(hull, Point(2.0l, 2.0l)));
	REQUIRE(!contains_point(hull, Point(1.0l, 1.0l)));
	REQUIRE(!contains_point(hull, Point(3.0l, 1.0l)));
}

TEST_CASE("collinear_points_on_boundary") {
	vector<Point> points = {{0.0l, 0.0l}, {1.0l, 0.0l}, {2.0l, 0.0l},
							{3.0l, 0.0l}, {3.0l, 1.0l}, {3.0l, 2.0l},
							{2.0l, 2.0l}, {1.0l, 2.0l}, {0.0l, 2.0l},
							{0.0l, 1.0l}, {1.5l, 1.0l}};
	auto hull = andrew(points);
	REQUIRE(hull.size() == 4);
	ensure_point_eq(hull[0], Point(0.0l, 0.0l));
	ensure_point_eq(hull[1], Point(3.0l, 0.0l));
	ensure_point_eq(hull[2], Point(3.0l, 2.0l));
	ensure_point_eq(hull[3], Point(0.0l, 2.0l));
}