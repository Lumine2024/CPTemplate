#pragma once
#include "geo/basic.h"

ld nearest(vector<Point> pts) {
	if(pts.size() == 1) return 0.0l;
	ld ans = 1e18l;
	sort(pts.begin(), pts.end(), [](const Point &a, const Point &b) {
		return a.x < b.x || (a.x == b.x && a.y < b.y);
	});
	auto part = [&](auto &&part, int l, int r) -> void {
		if(r - l < 5) {
			for(int i = l; i < r; ++i) {
				for(int j = i + 1; j < r; ++j) {
					ans = min(ans, dist(pts[i], pts[j]));
				}
			}
			sort(pts.begin() + l, pts.begin() + r,
				 [](const Point &a, const Point &b) { return a.y < b.y; });
			return;
		}
		int mid = (l + r) / 2;
		ld midx = pts[mid].x;
		part(part, l, mid);
		part(part, mid, r);
		inplace_merge(pts.begin() + l, pts.begin() + mid, pts.begin() + r,
					  [](const Point &a, const Point &b) { return a.y < b.y; });
		vector<Point> tmp;
		for(int i = l; i < r; ++i) {
			if(abs(pts[i].x - midx) < ans) {
				for(int j = int(tmp.size()) - 1;
					j >= 0 && pts[i].y - tmp[j].y < ans; --j) {
					ans = min(ans, dist(pts[i], tmp[j]));
				}
				tmp.push_back(pts[i]);
			}
		}
	};
	part(part, 0, pts.size());
	return ans;
}
