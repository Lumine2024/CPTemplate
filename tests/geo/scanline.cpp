#include "geo/scanline.h"
#include "../test.h"

TEST(scanline_single_rectangle) {
	vector<Rectangle> rects = {
		{Point(0.0l, 0.0l), Point(2.0l, 2.0l)},
	};
	ENSURE(cmp(scanline(rects), 4.0l) == 0);
}

TEST(scanline_overlapping_rectangles) {
	vector<Rectangle> rects = {
		{Point(0.0l, 0.0l), Point(2.0l, 2.0l)},
		{Point(1.0l, 0.0l), Point(3.0l, 2.0l)},
		{Point(1.0l, 1.0l), Point(2.0l, 3.0l)},
	};
	ENSURE(cmp(scanline(rects), 7.0l) == 0);
}
