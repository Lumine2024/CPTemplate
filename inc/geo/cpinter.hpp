
#pragma once
#include "constants.hpp"
#include "geo/basic.hpp"

ld sector_area(Circle c, Point u, Point v) {
	u = u - c.c, v = v - c.c, c.c = {};
	ld alp = angle(u, v);
	if(cmp(alp, pi) == 1) alp -= 2 * pi;
	return c.r * c.r * alp / 2;
}
ld inter_helper(Circle c, Point a, Point b) {
	a = a - c.c, b = b - c.c, c.c = {};
	ld da = a.len(), db = b.len();
	if(cmp(da, c.r) <= 0 && cmp(db, c.r) <= 0) {
		return cross(a, b) / 2;
	}
	ld di = dist(c.c, Lineseg{ a, b });
	if(cmp(di, c.r) >= 0) {
		return sector_area(c, a, b);
	}
	auto [ia, ib] = inter(c, Line{ a, b - a });
	Vector d = (b - a) / (b - a).len();
	ld ta = dot(ia - a, d), tb = dot(ib - a, d);
	if(ta > tb) swap(ia, ib);
	if(cmp(c.r, da) >= 0) {
		return cross(a, ib) / 2 + sector_area(c, ib, b);
	} else if(cmp(c.r, db) >= 0) {
		return cross(ia, b) / 2 + sector_area(c, a, ia);
	} else {
		return cross(ia, ib) / 2 + sector_area(c, a, ia) + sector_area(c, ib, b);
	}
}
ld inter_area(const Polygon &poly, const Circle &c) {
	ld ret = 0.0l;
	for(int i = 0; i < poly.size(); ++i) {
		int j = (i + 1) % poly.size();
		ret += inter_helper(c, poly.pts[i], poly.pts[j]);
	}
	return abs(ret);
}