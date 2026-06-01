#include "geo/pick.h"
#include "doctest.h"

TEST_CASE("pick_unit_square") {
	// Unit square: area=1, border=4, interior=0
	Polygon sq({Point(0, 0), Point(1, 0), Point(1, 1), Point(0, 1)});
	REQUIRE(sq.twice_area() == 2);
	REQUIRE(points_inside(sq) == 0);
}

TEST_CASE("pick_2x2_square") {
	// 2x2 square: area=4, border=8, interior=1
	Polygon sq({Point(0, 0), Point(2, 0), Point(2, 2), Point(0, 2)});
	REQUIRE(sq.twice_area() == 8);
	REQUIRE(points_inside(sq) == 1);
}

TEST_CASE("pick_3x4_rectangle") {
	// 3x4 rectangle: area=12, border=14, interior=6
	Polygon rect({Point(0, 0), Point(4, 0), Point(4, 3), Point(0, 3)});
	REQUIRE(rect.twice_area() == 24);
	REQUIRE(points_inside(rect) == 6);
}

TEST_CASE("pick_right_triangle") {
	// Triangle (0,0),(4,0),(0,3): area=6, border=4+3+1=8, interior=3
	Polygon tri({Point(0, 0), Point(4, 0), Point(0, 3)});
	REQUIRE(tri.twice_area() == 12);
	REQUIRE(points_inside(tri) == 3);
}

TEST_CASE("pick_lattice_triangle") {
	// Triangle (0,0),(6,0),(0,4): border=gcd(6,0)+gcd(6,4)+gcd(4,0)=6+2+4=12,
	// area=12, interior=(24-12+2)/2=7
	Polygon tri({Point(0, 0), Point(6, 0), Point(0, 4)});
	REQUIRE(tri.twice_area() == 24);
	REQUIRE(points_inside(tri) == 7);
}
