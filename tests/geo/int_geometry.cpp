#include "geo/int/andrew.h"
#include "geo/int/convex.h"
#include "geo/int/scanline.h"
#include "doctest.h"

static void ensure_points_set_eq(vector<PointInt> got,
								 vector<PointInt> expected) {
	auto cmp_point = [](const PointInt &a, const PointInt &b) {
		return a.x < b.x || (a.x == b.x && a.y < b.y);
	};
	sort(got.begin(), got.end(), cmp_point);
	sort(expected.begin(), expected.end(), cmp_point);
	REQUIRE(got.size() == expected.size());
	for(int i = 0; i < (int)got.size(); ++i) REQUIRE(got[i] == expected[i]);
}

TEST_CASE("integer_line_segments") {
	LineSegInt a(PointInt(0, 0), PointInt(4, 0));
	LineSegInt b(PointInt(2, -1), PointInt(2, 1));
	LineSegInt c(PointInt(4, 0), PointInt(5, 1));
	REQUIRE(is_on(PointInt(2, 0), a) == 1);
	REQUIRE(is_on(PointInt(0, 0), a) == 2);
	REQUIRE(is_on(PointInt(5, 0), a) == 0);
	REQUIRE(is_inter(a, b) == 1);
	REQUIRE(is_inter(a, c) == 2);
}

TEST_CASE("integer_andrew") {
	vector<PointInt> points = {{0, 0}, {3, 0}, {3, 2}, {0, 2},
							   {1, 0}, {1, 1}, {3, 1}, {0, 0}};
	auto hull = andrew(points);
	REQUIRE(hull.size() == 4);
	REQUIRE(hull[0] == PointInt(0, 0));
	REQUIRE(hull[1] == PointInt(3, 0));
	REQUIRE(hull[2] == PointInt(3, 2));
	REQUIRE(hull[3] == PointInt(0, 2));
}

TEST_CASE("integer_convex_queries") {
	vector<PointInt> cv = {{0, 0}, {4, 0}, {4, 3}, {0, 3}};
	auto [i, j] = convex_farthest(cv);
	REQUIRE(dist2(cv[i], cv[j]) == 25);
	auto tri = convex_max_triangle(cv);
	REQUIRE(abs(cross(cv[tri[0]], cv[tri[1]], cv[tri[2]])) == 12);
	REQUIRE(is_in_convex(PointInt(2, 1), cv));
	REQUIRE(is_in_convex(PointInt(4, 2), cv));
	REQUIRE(!is_in_convex(PointInt(5, 2), cv));

	auto tangent = convex_tangent(PointInt(5, 4), cv);
	REQUIRE(tangent.has_value());
	ensure_points_set_eq({tangent->first, tangent->second},
						 {PointInt(4, 0), PointInt(0, 3)});
	auto support = convex_tangent(LineInt(PointInt(), PointInt(1, 0)), cv);
	REQUIRE(min(support.first.y, support.second.y) == 0);
	REQUIRE(max(support.first.y, support.second.y) == 3);
}

TEST_CASE("integer_minkowski") {
	vector<PointInt> a = {{0, 0}, {2, 0}, {2, 1}, {0, 1}};
	vector<PointInt> b = {{1, 2}, {4, 2}, {4, 4}, {1, 4}};
	ensure_points_set_eq(minkowski_add(a, b), {{1, 2}, {6, 2}, {6, 5}, {1, 5}});
	ensure_points_set_eq(minkowski_sub(a, b),
						 {{-4, -4}, {1, -4}, {1, -1}, {-4, -1}});
}

TEST_CASE("integer_scanline") {
	vector<RectangleInt> rectangles = {
		{PointInt(0, 0), PointInt(2, 2)},
		{PointInt(1, 0), PointInt(3, 2)},
		{PointInt(1, 1), PointInt(2, 3)},
	};
	REQUIRE(scanline(rectangles) == 7);

	vector<RectangleInt> large = {
		{PointInt(0, 0), PointInt(1000000000, 1000000000)},
	};
	REQUIRE(scanline(large) == 1000000000000000000LL);
}
