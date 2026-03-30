#include "rotcal.h"
#include "../test.h"

TEST(rotcal_simple_segment) {
	// Two points: farthest distance squared = distance^2
	vector<Point> pts = {Point(0.0l, 0.0l), Point(3.0l, 4.0l)};
	ENSURE(cmp(farthest_dist(pts), 25.0l) == 0);
}

TEST(rotcal_square) {
	// Unit square: farthest pair is diagonal with distance^2 = 2
	vector<Point> pts = {
		Point(0.0l, 0.0l), Point(1.0l, 0.0l),
		Point(1.0l, 1.0l), Point(0.0l, 1.0l)};
	ENSURE(cmp(farthest_dist(pts), 2.0l) == 0);
}

TEST(rotcal_rectangle) {
	// 3x4 rectangle: farthest pair is diagonal with distance^2 = 25
	vector<Point> pts = {
		Point(0.0l, 0.0l), Point(4.0l, 0.0l),
		Point(4.0l, 3.0l), Point(0.0l, 3.0l)};
	ENSURE(cmp(farthest_dist(pts), 25.0l) == 0);
}

TEST(rotcal_with_interior_points) {
	// Interior points don't affect the result
	vector<Point> pts = {
		Point(0.0l, 0.0l), Point(4.0l, 0.0l), Point(4.0l, 3.0l),
		Point(0.0l, 3.0l), Point(2.0l, 1.5l)};
	ENSURE(cmp(farthest_dist(pts), 25.0l) == 0);
}

TEST(rotcal_collinear) {
	// Collinear points: max distance squared = (5-0)^2 = 25
	vector<Point> pts = {
		Point(0.0l, 0.0l), Point(2.0l, 0.0l),
		Point(3.0l, 0.0l), Point(5.0l, 0.0l)};
	ENSURE(cmp(farthest_dist(pts), 25.0l) == 0);
}
