#pragma once
#include "geo/basic.h"

Circle cover(const Point &a) {
	return Circle(a, 0);
}
Circle cover(const Point &a, const Point &b) {
	return Circle((a + b) / 2, (b - a).len() / 2);
}
Circle cover(const Point &a, const Point &b, const Point &c) {
	Line u = midperp(a, b), v = midperp(a, c);
	auto center = inter(u, v);
	if(!center) {
		Point d = min({a, b, c}), e = max({a, b, c});
		return Circle((d + e) / 2, (e - d).len() / 2);
	}
	return Circle(*center, dist(*center, a));
}
Circle cover(vector<Point> pts) {
	static mt19937 rng(
		(unsigned)chrono::steady_clock::now().time_since_epoch().count());
	shuffle(pts.begin(), pts.end(), rng);
	if(pts.size() == 1) return cover(pts[0]);
	if(pts.size() == 2) return cover(pts[0], pts[1]);
	if(pts.size() == 3) return cover(pts[0], pts[1], pts[2]);
	int n = pts.size();
	Circle ret = cover(pts[0]);
	for(int i = 1; i < n; ++i) {
		if(ret.r < dist(ret.c, pts[i])) {
			ret = cover(pts[i]);
			for(int j = 0; j < i; ++j) {
				if(ret.r < dist(ret.c, pts[j])) {
					ret = cover(pts[i], pts[j]);
					for(int k = 0; k < j; ++k) {
						if(ret.r < dist(ret.c, pts[k])) {
							ret = cover(pts[i], pts[j], pts[k]);
						}
					}
				}
			}
		}
	}
	return ret;
}
