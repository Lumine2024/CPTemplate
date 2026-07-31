#include "geo/fp/basic.h"
#include "doctest.h"

static void ensure_point_eq(const Point &a, const Point &b) {
	REQUIRE(a == b);
}

TEST_CASE("ld_cmp") {
	REQUIRE(sign(0.0l) == 0);
	REQUIRE(sign(1e-12l) == 0);
	REQUIRE(sign(1e-2l) == 1);
	REQUIRE(sign(1.0l) == 1);
	REQUIRE(sign(-1e-12l) == 0);
	REQUIRE(sign(-1e-2l) == -1);
	REQUIRE(sign(-1.0l) == -1);
	REQUIRE(cmp(0.0l, 1e-12l) == 0);
}

TEST_CASE("point_operators") {
	Point a(2.0l, 3.0l), b(4.0l, 5.0l);
	Point c = a + b;
	REQUIRE(cmp(c.x, 6.0l) == 0);
	REQUIRE(cmp(c.y, 8.0l) == 0);
}

TEST_CASE("point_vector_basic") {
	Point a(3.0l, 4.0l), b(1.0l, -2.0l);
	Point c = a - b;
	REQUIRE(cmp(c.x, 2.0l) == 0);
	REQUIRE(cmp(c.y, 6.0l) == 0);

	Point d = a * 2.5l;
	REQUIRE(cmp(d.x, 7.5l) == 0);
	REQUIRE(cmp(d.y, 10.0l) == 0);

	Point e = d / 2.5l;
	ensure_point_eq(e, a);
	REQUIRE(cmp(a.len2(), 25.0l) == 0);
	REQUIRE(cmp(a.len(), 5.0l) == 0);
}

TEST_CASE("point_arg_rotate") {
	Point x(1.0l, 0.0l), y(0.0l, 1.0l), z(-1.0l, 0.0l);
	REQUIRE(cmp(x.arg(), 0.0l) == 0);
	REQUIRE(cmp(y.arg(), pi / 2.0l) == 0);
	REQUIRE(cmp(z.arg(), pi) == 0);

	Point r = x.rotate(pi / 2.0l);
	REQUIRE(cmp(r.x, 0.0l) == 0);
	REQUIRE(cmp(r.y, 1.0l) == 0);
}

TEST_CASE("dot_cross_dist_angle") {
	Point a(1.0l, 0.0l), b(0.0l, 1.0l), c(2.0l, 3.0l);
	REQUIRE(cmp(dot(a, b), 0.0l) == 0);
	REQUIRE(cmp(cross(a, b), 1.0l) == 0);
	REQUIRE(cmp(dist(Point(0.0l, 0.0l), Point(3.0l, 4.0l)), 5.0l) == 0);
	REQUIRE(cmp(dist2(Point(0.0l, 0.0l), Point(3.0l, 4.0l)), 25.0l) == 0);
	REQUIRE(cmp(angle(a, b), pi / 2.0l) == 0);
	REQUIRE(cmp(angle(b, a), 3.0l * pi / 2.0l) == 0);
	REQUIRE(to_left(a, b) == 1);
	REQUIRE(to_left(c, a) == -1);
}

TEST_CASE("line_basic") {
	Line l1(Point(0.0l, 0.0l), Point(1.0l, 1.0l));
	Line l2(Point(0.0l, 2.0l), Point(1.0l, -1.0l));
	REQUIRE(is_inter(l1, l2) == 1);
	opt<Point> p = inter(l1, l2);
	REQUIRE(p.has_value());
	ensure_point_eq(*p, Point(1.0l, 1.0l));

	Point q(2.0l, 0.0l);
	Point proj_q = proj(q, l1);
	ensure_point_eq(proj_q, Point(1.0l, 1.0l));
	REQUIRE(cmp(dist(q, l1), sqrt(2.0l)) == 0);

	Line l3(Point(0.0l, 1.0l), Point(2.0l, 2.0l));
	REQUIRE(parallel(l1, l3));
	REQUIRE(cmp(dist(l1, l3), sqrt(2.0l) / 2.0l) == 0);
	REQUIRE(is_on(Point(3.0l, 3.0l), l1));
	REQUIRE(!is_on(Point(3.0l, 2.0l), l1));
}

TEST_CASE("lineseg_basic") {
	LineSeg s1(Point(0.0l, 0.0l), Point(4.0l, 0.0l));
	LineSeg s2(Point(2.0l, -1.0l), Point(2.0l, 1.0l));
	REQUIRE(is_inter(s1, s2) == 1);
	REQUIRE(is_on(Point(2.0l, 0.0l), s1) == 1);
	REQUIRE(is_on(Point(0.0l, 0.0l), s1) == 2);
	REQUIRE(is_on(Point(5.0l, 0.0l), s1) == 0);

	Line lx(Point(0.0l, 1.0l), Point(1.0l, 0.0l));
	REQUIRE(is_inter(lx, s2) == 2);
	opt<Point> ip = inter(lx, s2);
	REQUIRE(ip.has_value());
	ensure_point_eq(*ip, Point(2.0l, 1.0l));
	REQUIRE(cmp(dist(Point(3.0l, 2.0l), s1), 2.0l) == 0);
}

TEST_CASE("polygon_circle_basic") {
	vector<Point> tri = {Point(0.0l, 0.0l), Point(4.0l, 0.0l),
						 Point(0.0l, 3.0l)};
	REQUIRE(cmp(poly_area(tri), 6.0l) == 0);
	REQUIRE(cmp(poly_circ(tri), 12.0l) == 0);

	Circle c(Point(0.0l, 0.0l), 2.0l);
	REQUIRE(cmp(c.area(), 4.0l * pi) == 0);
	REQUIRE(cmp(c.circ(), 4.0l * pi) == 0);
}

TEST_CASE("circle_intersections") {
	Circle c1(Point(0.0l, 0.0l), 5.0l), c2(Point(8.0l, 0.0l), 5.0l);
	REQUIRE(is_inter(c1, c2));
	opt<pair<Point, Point>> ic = inter(c1, c2);
	REQUIRE(ic.has_value());
	REQUIRE(cmp(dist(ic->first, c1.c), c1.r) == 0);
	REQUIRE(cmp(dist(ic->first, c2.c), c2.r) == 0);
	REQUIRE(cmp(dist(ic->second, c1.c), c1.r) == 0);
	REQUIRE(cmp(dist(ic->second, c2.c), c2.r) == 0);

	Line l(Point(-10.0l, 0.0l), Point(1.0l, 0.0l));
	opt<pair<Point, Point>> il = inter(c1, l);
	REQUIRE(il.has_value());
	REQUIRE(cmp(dist(il->first, c1.c), c1.r) == 0);
	REQUIRE(cmp(dist(il->second, c1.c), c1.r) == 0);
	REQUIRE(cmp(il->first.y, 0.0l) == 0);
	REQUIRE(cmp(il->second.y, 0.0l) == 0);
}
