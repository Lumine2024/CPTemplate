#include "andrew.h"
#include "../test.h"

static void ensure_point_eq(const Point &a, const Point &b) {
	ENSURE(cmp(a.x, b.x) == 0);
	ENSURE(cmp(a.y, b.y) == 0);
}

static bool contains_point(const vector<Point> &pts, const Point &p) {
	for(const auto &x : pts) {
		if(x == p) return true;
	}
	return false;
}

TEST(simple_convex) {
	vector<Point> points = {
		{0.0l, 0.0l}, {1.0l, 0.0l}, {1.0l, 1.0l}, {0.0l, 1.0l}};
	auto convex = andrew(points);
	ENSURE(convex.size() == 4);
	ensure_point_eq(convex[0], Point(0.0l, 0.0l));
	ensure_point_eq(convex[1], Point(1.0l, 0.0l));
	ensure_point_eq(convex[2], Point(1.0l, 1.0l));
	ensure_point_eq(convex[3], Point(0.0l, 1.0l));
}

TEST(degenerate_cases) {
	vector<Point> one = {{2.0l, -3.0l}};
	auto hull_one = andrew(one);
	ENSURE(hull_one.size() == 1);
	ensure_point_eq(hull_one[0], Point(2.0l, -3.0l));

	vector<Point> two = {{5.0l, 1.0l}, {-1.0l, 4.0l}};
	auto hull_two = andrew(two);
	ENSURE(hull_two.size() == 2);
	ensure_point_eq(hull_two[0], Point(-1.0l, 4.0l));
	ensure_point_eq(hull_two[1], Point(5.0l, 1.0l));

	vector<Point> all_same = {
		{1.5l, 1.5l}, {1.5l, 1.5l}, {1.5l, 1.5l}, {1.5l, 1.5l}};
	auto hull_same = andrew(all_same);
	ENSURE(hull_same.size() == 1);
	ensure_point_eq(hull_same[0], Point(1.5l, 1.5l));
}

TEST(collinear_points) {
	vector<Point> points = {{-3.0l, 0.0l}, {0.0l, 0.0l}, {2.0l, 0.0l},
							{5.0l, 0.0l},  {2.0l, 0.0l}, {-1.0l, 0.0l}};
	auto hull = andrew(points);
	ENSURE(hull.size() == 2);
	ensure_point_eq(hull[0], Point(-3.0l, 0.0l));
	ensure_point_eq(hull[1], Point(5.0l, 0.0l));
}

TEST(duplicates_and_interior_points) {
	vector<Point> points = {{0.0l, 0.0l}, {4.0l, 0.0l}, {4.0l, 4.0l},
							{0.0l, 4.0l}, {2.0l, 2.0l}, {1.0l, 1.0l},
							{3.0l, 1.0l}, {0.0l, 0.0l}, {4.0l, 0.0l}};
	auto hull = andrew(points);
	ENSURE(hull.size() == 4);
	ENSURE(contains_point(hull, Point(0.0l, 0.0l)));
	ENSURE(contains_point(hull, Point(4.0l, 0.0l)));
	ENSURE(contains_point(hull, Point(4.0l, 4.0l)));
	ENSURE(contains_point(hull, Point(0.0l, 4.0l)));
	ENSURE(!contains_point(hull, Point(2.0l, 2.0l)));
	ENSURE(!contains_point(hull, Point(1.0l, 1.0l)));
	ENSURE(!contains_point(hull, Point(3.0l, 1.0l)));
}

TEST(collinear_points_on_boundary) {
	vector<Point> points = {{0.0l, 0.0l}, {1.0l, 0.0l}, {2.0l, 0.0l},
							{3.0l, 0.0l}, {3.0l, 1.0l}, {3.0l, 2.0l},
							{2.0l, 2.0l}, {1.0l, 2.0l}, {0.0l, 2.0l},
							{0.0l, 1.0l}, {1.5l, 1.0l}};
	auto hull = andrew(points);
	ENSURE(hull.size() == 4);
	ensure_point_eq(hull[0], Point(0.0l, 0.0l));
	ensure_point_eq(hull[1], Point(3.0l, 0.0l));
	ensure_point_eq(hull[2], Point(3.0l, 2.0l));
	ensure_point_eq(hull[3], Point(0.0l, 2.0l));
}