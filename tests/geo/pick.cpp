#include "geo/int/pick.h"
#include "doctest.h"

TEST_CASE("pick_unit_square") {
	// Unit square: area=1, border=4, interior=0
	vector<PointInt> sq = {PointInt(0, 0), PointInt(1, 0), PointInt(1, 1),
						   PointInt(0, 1)};
	REQUIRE(polygon_twice_area(sq) == 2);
	REQUIRE(points_inside(sq) == 0);
}

TEST_CASE("pick_2x2_square") {
	// 2x2 square: area=4, border=8, interior=1
	vector<PointInt> sq = {PointInt(0, 0), PointInt(2, 0), PointInt(2, 2),
						   PointInt(0, 2)};
	REQUIRE(polygon_twice_area(sq) == 8);
	REQUIRE(points_inside(sq) == 1);
}

TEST_CASE("pick_3x4_rectangle") {
	// 3x4 rectangle: area=12, border=14, interior=6
	vector<PointInt> rect = {PointInt(0, 0), PointInt(4, 0), PointInt(4, 3),
							 PointInt(0, 3)};
	REQUIRE(polygon_twice_area(rect) == 24);
	REQUIRE(points_inside(rect) == 6);
}

TEST_CASE("pick_right_triangle") {
	// Triangle (0,0),(4,0),(0,3): area=6, border=4+3+1=8, interior=3
	vector<PointInt> tri = {PointInt(0, 0), PointInt(4, 0), PointInt(0, 3)};
	REQUIRE(polygon_twice_area(tri) == 12);
	REQUIRE(points_inside(tri) == 3);
}

TEST_CASE("pick_lattice_triangle") {
	// Triangle (0,0),(6,0),(0,4): border=gcd(6,0)+gcd(6,4)+gcd(4,0)=6+2+4=12,
	// area=12, interior=(24-12+2)/2=7
	vector<PointInt> tri = {PointInt(0, 0), PointInt(6, 0), PointInt(0, 4)};
	REQUIRE(polygon_twice_area(tri) == 24);
	REQUIRE(points_inside(tri) == 7);
}
