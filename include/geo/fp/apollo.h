#pragma once
#include "geo/fp/basic.h"

// PA / PB = lam
opt<Circle> apollonius(const Point &a, const Point &b, ld lam) {
	if(cmp(lam, 1) == 0) return nul;
	if(lam > 1) return apollonius(b, a, 1.0l / lam);
	Point v = b - a;
	Point p1 = a + v / (1 + lam) * lam, p2 = a - v / (1 - lam) * lam;
	return Circle((p1 + p2) / 2, dist(p1, p2) / 2);
}
