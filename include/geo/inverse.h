#pragma once
#include "geo/basic.h"

// (A invert to C)'s shape, true is circle, false is line
bool inv_shape(const Circle &c, const Circle &a) {
	return cmp(dist(c.c, a.c), a.r) != 0;
}
bool inv_shape(const Circle &c, const Line &l) {
	return sign(cross(c.c - l.p, l.v)) != 0;
}
Point inverse(const Circle &c, const Point &a) {
	Point v = a - c.c;
	return c.c + v * (c.r * c.r / v.len());
}
opt<Circle> invcircle(const Circle &c, const Circle &a) {
	if(!inv_shape(c, a)) return nul;
	Point v = a.c - c.c;
	Point p1 = a.c - v / v.len() * a.r, p2 = a.c + v / v.len() * a.r;
	Point p3 = inverse(c, p1), p4 = inverse(c, p2);
	return Circle((p3 + p4) / 2, dist(p3, p4) / 2);
}
opt<Line> invline(const Circle &c, const Circle &a) {
	if(inv_shape(c, a)) return nul;
	Point v = a.c - c.c;
	Point pt = c.c + v * 2;
	Point ip = inverse(c, pt);
	return Line(ip, Point(-v.y, v.x));
}
opt<Circle> invcircle(const Circle &c, const Line &l) {
	if(!inv_shape(c, l)) return nul;
	Point p1 = l.p, p2 = l.p + l.v, p3 = l.p - l.v;
	Point q1 = inverse(c, p1), q2 = inverse(c, p2), q3 = inverse(c, p3);
	ld x1 = q1.x, y1 = q1.y;
	ld x2 = q2.x, y2 = q2.y;
	ld x3 = q3.x, y3 = q3.y;
	ld A = x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2);
	ld S1 = q1.len2(), S2 = q2.len2(), S3 = q3.len2();
	ld ux = (S1 * (y2 - y3) + S2 * (y3 - y1) + S3 * (y1 - y2)) / (2 * A);
	ld uy = (S1 * (x3 - x2) + S2 * (x1 - x3) + S3 * (x2 - x1)) / (2 * A);
	Point o(ux, uy);
	ld r = dist(o, q1);
	return Circle(o, r);
}
opt<Line> invline(const Circle &c, const Line &l) {
	if(inv_shape(c, l)) return nul;
	return l;
}
