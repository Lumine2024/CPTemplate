#include "geo/basic.h"
#include "../test.h"

static void ensure_point_eq(const Point &a, const Point &b) {
	ENSURE(cmp(a.x, b.x) == 0);
	ENSURE(cmp(a.y, b.y) == 0);
}

TEST(ld_cmp) {
	ENSURE(sign(0.0l) == 0);
	ENSURE(sign(1e-12l) == 0);
	ENSURE(sign(1e-2l) == 1);
	ENSURE(sign(1.0l) == 1);
	ENSURE(sign(-1e-12l) == 0);
	ENSURE(sign(-1e-2l) == -1);
	ENSURE(sign(-1.0l) == -1);
	ENSURE(cmp(0.0l, 1e-12l) == 0);
}

TEST(point_operators) {
	Point a(2.0l, 3.0l), b(4.0l, 5.0l);
	Point c = a + b;
	ENSURE(cmp(c.x, 6.0l) == 0);
	ENSURE(cmp(c.y, 8.0l) == 0);
}

TEST(point_vector_basic) {
	Point a(3.0l, 4.0l), b(1.0l, -2.0l);
	Point c = a - b;
	ENSURE(cmp(c.x, 2.0l) == 0);
	ENSURE(cmp(c.y, 6.0l) == 0);

	Point d = a * 2.5l;
	ENSURE(cmp(d.x, 7.5l) == 0);
	ENSURE(cmp(d.y, 10.0l) == 0);

	Point e = d / 2.5l;
	ensure_point_eq(e, a);
	ENSURE(cmp(a.len2(), 25.0l) == 0);
	ENSURE(cmp(a.len(), 5.0l) == 0);
}

TEST(point_arg_rotate) {
	Point x(1.0l, 0.0l), y(0.0l, 1.0l), z(-1.0l, 0.0l);
	ENSURE(cmp(x.arg(), 0.0l) == 0);
	ENSURE(cmp(y.arg(), pi / 2.0l) == 0);
	ENSURE(cmp(z.arg(), pi) == 0);

	Point r = x.rotate(pi / 2.0l);
	ENSURE(cmp(r.x, 0.0l) == 0);
	ENSURE(cmp(r.y, 1.0l) == 0);
}

TEST(dot_cross_dist_angle) {
	Vector a(1.0l, 0.0l), b(0.0l, 1.0l), c(2.0l, 3.0l);
	ENSURE(cmp(dot(a, b), 0.0l) == 0);
	ENSURE(cmp(cross(a, b), 1.0l) == 0);
	ENSURE(cmp(dist(Point(0.0l, 0.0l), Point(3.0l, 4.0l)), 5.0l) == 0);
	ENSURE(cmp(dist2(Point(0.0l, 0.0l), Point(3.0l, 4.0l)), 25.0l) == 0);
	ENSURE(cmp(angle(a, b), pi / 2.0l) == 0);
	ENSURE(cmp(angle(b, a), 3.0l * pi / 2.0l) == 0);
	ENSURE(to_left(a, b) == 1);
	ENSURE(to_left(c, a) == -1);
}

TEST(line_basic) {
	Line l1(Point(0.0l, 0.0l), Vector(1.0l, 1.0l));
	Line l2(Point(0.0l, 2.0l), Vector(1.0l, -1.0l));
	ENSURE(is_inter(l1, l2) == 1);
	optional<Point> p = inter(l1, l2);
	ENSURE(p.has_value());
	ensure_point_eq(*p, Point(1.0l, 1.0l));

	Point q(2.0l, 0.0l);
	Point proj_q = proj(q, l1);
	ensure_point_eq(proj_q, Point(1.0l, 1.0l));
	ENSURE(cmp(dist(q, l1), sqrt(2.0l)) == 0);

	Line l3(Point(0.0l, 1.0l), Vector(2.0l, 2.0l));
	ENSURE(parallel(l1, l3));
	ENSURE(cmp(dist(l1, l3), sqrt(2.0l) / 2.0l) == 0);
	ENSURE(is_on(Point(3.0l, 3.0l), l1));
	ENSURE(!is_on(Point(3.0l, 2.0l), l1));
}

TEST(lineseg_basic) {
	Lineseg s1(Point(0.0l, 0.0l), Point(4.0l, 0.0l));
	Lineseg s2(Point(2.0l, -1.0l), Point(2.0l, 1.0l));
	ENSURE(is_inter(s1, s2) == 1);
	ENSURE(is_on(Point(2.0l, 0.0l), s1) == 1);
	ENSURE(is_on(Point(0.0l, 0.0l), s1) == 2);
	ENSURE(is_on(Point(5.0l, 0.0l), s1) == 0);

	Line lx(Point(0.0l, 1.0l), Vector(1.0l, 0.0l));
	ENSURE(is_inter(lx, s2) == 2);
	optional<Point> ip = inter(lx, s2);
	ENSURE(ip.has_value());
	ensure_point_eq(*ip, Point(2.0l, 1.0l));
	ENSURE(cmp(dist(Point(3.0l, 2.0l), s1), 2.0l) == 0);
}

TEST(polygon_circle_basic) {
	Polygon tri({Point(0.0l, 0.0l), Point(4.0l, 0.0l), Point(0.0l, 3.0l)});
	ENSURE(cmp(tri.area(), 6.0l) == 0);
	ENSURE(cmp(tri.circ(), 12.0l) == 0);

	Circle c(Point(0.0l, 0.0l), 2.0l);
	ENSURE(cmp(c.area(), 4.0l * pi) == 0);
	ENSURE(cmp(c.circ(), 4.0l * pi) == 0);
}

TEST(circle_intersections) {
	Circle c1(Point(0.0l, 0.0l), 5.0l), c2(Point(8.0l, 0.0l), 5.0l);
	ENSURE(is_inter(c1, c2));
	optional<pair<Point, Point>> ic = inter(c1, c2);
	ENSURE(ic.has_value());
	ENSURE(cmp(dist(ic->first, c1.c), c1.r) == 0);
	ENSURE(cmp(dist(ic->first, c2.c), c2.r) == 0);
	ENSURE(cmp(dist(ic->second, c1.c), c1.r) == 0);
	ENSURE(cmp(dist(ic->second, c2.c), c2.r) == 0);

	Line l(Point(-10.0l, 0.0l), Vector(1.0l, 0.0l));
	optional<pair<Point, Point>> il = inter(c1, l);
	ENSURE(il.has_value());
	ENSURE(cmp(dist(il->first, c1.c), c1.r) == 0);
	ENSURE(cmp(dist(il->second, c1.c), c1.r) == 0);
	ENSURE(cmp(il->first.y, 0.0l) == 0);
	ENSURE(cmp(il->second.y, 0.0l) == 0);
}