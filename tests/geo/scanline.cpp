#include "geo/fp/scanline.h"
#include "doctest.h"

TEST_CASE("scanline_single_rectangle") {
	vector<Rectangle> rects = {
		{Point(0.0l, 0.0l), Point(2.0l, 2.0l)},
	};
	REQUIRE(cmp(scanline(rects), 4.0l) == 0);
}

TEST_CASE("scanline_overlapping_rectangles") {
	vector<Rectangle> rects = {
		{Point(0.0l, 0.0l), Point(2.0l, 2.0l)},
		{Point(1.0l, 0.0l), Point(3.0l, 2.0l)},
		{Point(1.0l, 1.0l), Point(2.0l, 3.0l)},
	};
	REQUIRE(cmp(scanline(rects), 7.0l) == 0);
}
