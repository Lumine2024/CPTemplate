#pragma once
#include "basic.h"

// PA / PB = lambda
optional<Circle> apollonius(const Point &a, const Point &b, ld lambda) {
	if(cmp(lambda, 1) == 0) return nullopt;
	if(lambda > 1) return apollonius(b, a, 1.0l / lambda);
	Vector v = b - a;
	Point p1 = a + v / (1 + lambda) * lambda,
		  p2 = a - v / (1 - lambda) * lambda;
	return Circle((p1 + p2) / 2, dist(p1, p2) / 2);
}
