#include "geo/fp/andrew.h"
#include "geo/fp/convex.h"
#include "doctest.h"

static ld farthest_dist2(const vector<Point> &pts) {
	auto convex = andrew(pts);
	auto [i, j] = convex_farthest(convex);
	return dist2(convex[i], convex[j]);
}

static ld triangle_area2(const vector<Point> &convex, array<int, 3> tri) {
	return abs(cross(convex[tri[0]], convex[tri[1]], convex[tri[2]]));
}

static void ensure_points_set_eq(vector<Point> got, vector<Point> expected) {
	sort(got.begin(), got.end());
	sort(expected.begin(), expected.end());
	REQUIRE(got.size() == expected.size());
	for(int i = 0; i < (int)got.size(); ++i) REQUIRE(got[i] == expected[i]);
}

TEST_CASE("convex_farthest_simple_segment") {
	vector<Point> pts = {Point(0.0l, 0.0l), Point(3.0l, 4.0l)};
	REQUIRE(cmp(farthest_dist2(pts), 25.0l) == 0);
}

TEST_CASE("convex_farthest_square") {
	vector<Point> pts = {Point(0.0l, 0.0l), Point(1.0l, 0.0l),
						 Point(1.0l, 1.0l), Point(0.0l, 1.0l)};
	REQUIRE(cmp(farthest_dist2(pts), 2.0l) == 0);
}

TEST_CASE("convex_farthest_rectangle") {
	vector<Point> pts = {Point(0.0l, 0.0l), Point(4.0l, 0.0l),
						 Point(4.0l, 3.0l), Point(0.0l, 3.0l)};
	REQUIRE(cmp(farthest_dist2(pts), 25.0l) == 0);
}

TEST_CASE("convex_farthest_with_interior_points") {
	vector<Point> pts = {Point(0.0l, 0.0l), Point(4.0l, 0.0l),
						 Point(4.0l, 3.0l), Point(0.0l, 3.0l),
						 Point(2.0l, 1.5l)};
	REQUIRE(cmp(farthest_dist2(pts), 25.0l) == 0);
}

TEST_CASE("convex_farthest_collinear") {
	vector<Point> pts = {Point(0.0l, 0.0l), Point(2.0l, 0.0l),
						 Point(3.0l, 0.0l), Point(5.0l, 0.0l)};
	REQUIRE(cmp(farthest_dist2(pts), 25.0l) == 0);
}

TEST_CASE("convex_farthest_single_point") {
	vector<Point> convex = {Point(2.0l, -1.0l)};
	auto [i, j] = convex_farthest(convex);
	REQUIRE(i == 0);
	REQUIRE(j == 0);
}

TEST_CASE("convex_max_triangle") {
	vector<Point> convex = {Point(0.0l, 0.0l), Point(4.0l, 0.0l),
							Point(4.0l, 3.0l), Point(0.0l, 3.0l)};
	auto tri = convex_max_triangle(convex);
	REQUIRE(cmp(triangle_area2(convex, tri), 12.0l) == 0);
}

TEST_CASE("convex_point_inside") {
	vector<Point> convex = {Point(0.0l, 0.0l), Point(4.0l, 0.0l),
							Point(0.0l, 3.0l)};
	REQUIRE(is_in_convex(Point(1.0l, 1.0l), convex));
}

TEST_CASE("convex_point_not_inside") {
	vector<Point> convex = {Point(0.0l, 0.0l), Point(4.0l, 0.0l),
							Point(0.0l, 3.0l)};
	REQUIRE(!is_in_convex(Point(4.0l, 3.0l), convex));
}

TEST_CASE("convex_point_tangent_not_exist_when_point_is_in_convex") {
	vector<Point> convex = {Point(0.0l, 0.0l), Point(4.0l, 0.0l),
							Point(0.0l, 3.0l)};
	REQUIRE(!convex_tangent(Point(1.0l, 1.0l), convex).has_value());
}

TEST_CASE("convex_point_tangent") {
	vector<Point> convex = {Point(0.0l, 0.0l), Point(4.0l, 0.0l),
							Point(0.0l, 3.0l)};
	auto result = convex_tangent(Point(4.0l, 3.0l), convex);
	REQUIRE(result.has_value());
	pair<Point, Point> expected = {Point(4.0l, 0.0l), Point(0.0l, 3.0l)};
	REQUIRE(min(result->first, result->second) ==
			min(expected.first, expected.second));
	REQUIRE(max(result->first, result->second) ==
			max(expected.first, expected.second));
}

TEST_CASE("convex_line_tangent_square") {
	vector<Point> convex = {Point(0.0l, 0.0l), Point(2.0l, 0.0l),
							Point(2.0l, 2.0l), Point(0.0l, 2.0l)};
	auto result =
		convex_tangent(Line(Point(0.0l, -1.0l), Point(1.0l, 0.0l)), convex);
	REQUIRE(cmp(min(result.first.y, result.second.y), 0.0l) == 0);
	REQUIRE(cmp(max(result.first.y, result.second.y), 2.0l) == 0);
}

TEST_CASE("convex_line_tangent_slanted") {
	vector<Point> convex = {Point(0.0l, 0.0l), Point(4.0l, 0.0l),
							Point(4.0l, 1.0l), Point(1.0l, 3.0l),
							Point(0.0l, 2.0l)};
	auto result =
		convex_tangent(Line(Point(0.0l, 0.0l), Point(1.0l, 1.0l)), convex);
	ensure_points_set_eq({result.first, result.second},
						 {Point(4.0l, 0.0l), Point(0.0l, 2.0l)});
}

TEST_CASE("convex_minkowski_add_rectangles") {
	vector<Point> a = {Point(0.0l, 0.0l), Point(2.0l, 0.0l), Point(2.0l, 1.0l),
					   Point(0.0l, 1.0l)};
	vector<Point> b = {Point(1.0l, 2.0l), Point(4.0l, 2.0l), Point(4.0l, 4.0l),
					   Point(1.0l, 4.0l)};
	auto result = minkowski_add(a, b);
	ensure_points_set_eq(result, {Point(1.0l, 2.0l), Point(6.0l, 2.0l),
								  Point(6.0l, 5.0l), Point(1.0l, 5.0l)});
}

TEST_CASE("convex_minkowski_add_triangle_and_segment") {
	vector<Point> tri = {Point(0.0l, 0.0l), Point(2.0l, 0.0l),
						 Point(1.0l, 2.0l)};
	vector<Point> seg = {Point(-1.0l, 1.0l), Point(1.0l, 1.0l)};
	auto result = minkowski_add(tri, seg);
	ensure_points_set_eq(result, {Point(-1.0l, 1.0l), Point(3.0l, 1.0l),
								  Point(2.0l, 3.0l), Point(0.0l, 3.0l)});
}

TEST_CASE("convex_minkowski_sub_keeps_negated_polygon_orientation") {
	vector<Point> a = {Point(0.0l, 0.0l), Point(2.0l, 0.0l), Point(2.0l, 1.0l),
					   Point(0.0l, 1.0l)};
	vector<Point> b = {Point(1.0l, 2.0l), Point(4.0l, 2.0l), Point(4.0l, 4.0l),
					   Point(1.0l, 4.0l)};
	auto result = minkowski_sub(a, b);
	ensure_points_set_eq(result, {Point(-4.0l, -4.0l), Point(1.0l, -4.0l),
								  Point(1.0l, -1.0l), Point(-4.0l, -1.0l)});
}
