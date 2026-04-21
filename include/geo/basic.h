#pragma once
#include "common.h"

constexpr ld eps = 1e-9l, pi = numbers::pi_v<ld>, inf = 1e12l;
int sign(ld a) {
	return (a < -eps) ? -1 : (a > eps) ? 1 : 0;
}
int cmp(ld a, ld b) {
	return sign(a - b);
}
auto cmpso(ld a, ld b) {
	return cmp(a, b) <=> 0;
}

struct Point {
	ld x, y;
	Point() : x(0.0l), y(0.0l) {}
	Point(ld _x, ld _y) : x(_x), y(_y) {}
	Point(const complex<ld> &cd) : x(cd.real()), y(cd.imag()) {}
	operator complex<ld>() const {
		return complex<ld>(x, y);
	}
	ld len2() const {
		return x * x + y * y;
	}
	ld len() const {
		return sqrt(x * x + y * y);
	}
	// [0, 2pi)
	ld arg() const {
		ld ret = atan2(y, x);
		int c = cmp(ret, 0);
		return c == 1 ? ret : c == 0 ? 0.0l : ret + 2 * pi;
	}
	Point rotate(ld a) const {
		return Point(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
	}
	ld &operator[](int i) {
		return i == 0 ? x : y;
	}
	ld operator[](int i) const {
		return i == 0 ? x : y;
	}
	Point operator+(const Point &p) const {
		return Point(x + p.x, y + p.y);
	}
	Point operator-(const Point &p) const {
		return Point(x - p.x, y - p.y);
	}
	Point operator*(ld z) const {
		return Point(z * x, z * y);
	}
	friend Point operator*(ld z, const Point &p) {
		return p * z;
	}
	Point operator/(ld z) const {
		return Point(x / z, y / z);
	}
	bool operator==(const Point &p) const {
		return cmp(x, p.x) == 0 && cmp(y, p.y) == 0;
	}
	auto operator<=>(const Point &p) const {
		auto cx = cmpso(x, p.x);
		if(cx != 0) return cx;
		return cmpso(y, p.y);
	}
};
using Vector = Point;
ld dot(const Vector &x, const Vector &y) {
	return x.x * y.x + x.y * y.y;
}
ld cross(const Vector &x, const Vector &y) {
	return x.x * y.y - x.y * y.x;
}
ld cross(const Point &o, const Point &a, const Point &b) {
	return cross(a - o, b - o);
}
bool argcmp(const Point &x, const Point &y) {
	bool bx = sign(x.y) == 1 || (sign(x.y) == 0 && sign(x.x) == 1),
		 by = sign(y.y) == 1 || (sign(y.y) == 0 && sign(y.x) == 1);
	if(bx != by) return bx;
	return sign(cross(x, y)) == 1;
}
ld dist(const Point &x, const Point &y) {
	return (x - y).len();
}
ld dist2(const Point &x, const Point &y) {
	return (x - y).len2();
}
int to_left(const Vector &a, const Vector &b) {
	return sign(cross(a, b));
}
int to_left(const Point &a, const Point &b, const Point &c) {
	return sign(cross(a, b, c));
}
ld angle(const Vector &a, const Vector &b) {
	ld cosa = clamp(dot(a, b) / (a.len() * b.len()), -1.0l, 1.0l);
	ld ret = acos(cosa);
	if(to_left(a, b) == -1) {
		ret = 2 * pi - ret;
	}
	return ret;
}

struct Line {
	Point p, v;
	Line() {}
	Line(const Point &_p, const Vector &_v) : p(_p), v(_v) {}
	ld at(ld x) const {
		if(sign(v.x) == 0) return -inf;
		ld delx = x - p.x;
		ld ratio = delx / v.x;
		return (p + ratio * v).y;
	}
};
int to_left(const Line &ln, const Point &p) {
	return to_left(ln.v, p - ln.p);
}
bool parallel(const Line &l1, const Line &l2) {
	return sign(cross(l1.v, l2.v)) == 0;
}
int is_inter(const Line &l1, const Line &l2) {
	return parallel(l1, l2) ? 0 : 1;
}
optional<Point> inter(const Line &a, const Line &b) {
	if(parallel(a, b)) return nullopt;
	Vector v = a.v * (cross(b.v, a.p - b.p) / cross(a.v, b.v));
	return a.p + v;
}
ld dist(const Point &p, const Line &ln) {
	return abs(cross(ln.v, p - ln.p)) / ln.v.len();
}
ld dist(const Line &l1, const Line &l2) {
	if(!parallel(l1, l2)) return -1.0l;
	return dist(l1.p, l2);
}
Point proj(const Point &p, const Line &ln) {
	Vector v = ln.v * (dot(ln.v, p - ln.p) / (dot(ln.v, ln.v)));
	return ln.p + v;
}
bool is_on(const Point &p, const Line &ln) {
	return sign(cross(ln.v, ln.p - p)) == 0;
}
Line midperp(const Point &a, const Point &b) {
	Point mid = (a + b) / 2;
	Vector to(-(b - a).y, (b - a).x);
	return Line(mid, to);
}

struct Lineseg {
	Point a, b;
	Lineseg() {}
	Lineseg(const Point &_a, const Point &_b) : a(_a), b(_b) {}
	ld len() const {
		return (b - a).len();
	}
	ld at(ld x) const {
		if(cmp(x, min(a.x, b.x)) == -1 || cmp(x, max(a.x, b.x)) == 1)
			return -inf;
		if(cmp(a.x, b.x) == 0) {
			if(cmp(a.x, x) != 0) return -inf;
			return max(a.y, b.y);
		}
		Line l(a, b - a);
		return l.at(x);
	}
};
int is_on(const Point &p, const Lineseg &ls) {
	if(p == ls.a || p == ls.b) return 2;
	return to_left(p - ls.a, p - ls.b) == 0 &&
		   sign(dot(p - ls.a, p - ls.b)) == -1;
}
int is_inter(const Line &ln, const Lineseg &ls) {
	int a = to_left(ln, ls.a), b = to_left(ln, ls.b);
	if(a == 0 || b == 0) return 2;
	return a == b ? 0 : 1;
}
optional<Point> inter(const Line &ln, const Lineseg &ls) {
	if(!is_inter(ln, ls)) return nullopt;
	return inter(ln, Line(ls.a, ls.b - ls.a));
}
int is_inter(const Lineseg &l1, const Lineseg &l2) {
	if(is_on(l1.a, l2) || is_on(l1.b, l2) || is_on(l2.a, l1) || is_on(l2.b, l1))
		return 2;
	Line ln1(l1.a, l1.b - l1.a), ln2(l2.a, l2.b - l2.a);
	return to_left(ln1, l2.a) * to_left(ln1, l2.b) == -1 &&
		   to_left(ln2, l1.a) * to_left(ln2, l1.b) == -1;
}
ld dist(const Point &p, const Lineseg &ls) {
	if(is_on(p, ls) != 0) return 0.0l;
	if(sign(dot(p - ls.a, ls.b - ls.a)) == -1 ||
	   sign(dot(p - ls.b, ls.a - ls.b)) == -1)
		return min(dist(p, ls.a), dist(p, ls.b));
	Line l(ls.a, ls.b - ls.a);
	return dist(p, l);
}

struct Polygon {
	vector<Point> pts;
	Polygon() {}
	Polygon(const vector<Point> &p) : pts(p) {}
	Polygon(const vector<Line> &l) {
		pts.reserve(l.size());
		for(int i = 0; i < (int)l.size(); ++i) {
			pts.emplace_back(*inter(l[i], l[(i + 1) % l.size()]));
		}
	}
	ld area() const {
		ld ret = 0.0l;
		for(int i = 0; i < (int)pts.size(); ++i) {
			ret += cross(pts[i], pts[(i + 1) % pts.size()]);
		}
		return ret / 2.0l;
	}
	ld circ() const {
		ld ret = 0.0l;
		for(int i = 0; i < (int)pts.size(); ++i) {
			ret += (pts[i] - pts[(i + 1) % pts.size()]).len();
		}
		return ret;
	}
	int size() const {
		return pts.size();
	}
};

struct Circle {
	Point c;
	ld r;
	Circle() : r(0.0l) {}
	Circle(const Point &_c, ld _r) : c(_c), r(_r) {}
	ld area() const {
		return pi * r * r;
	}
	ld circ() const {
		return 2.0l * pi * r;
	}
};
bool is_inter(const Circle &c1, const Circle &c2) {
	ld dis = (c2.c - c1.c).len();
	ld r1 = c1.r, r2 = c2.r;
	if(abs(dis) <= eps) return false;
	if(dis > r1 + r2 + eps || dis < abs(r1 - r2) - eps) return false;
	return true;
}
optional<pair<Point, Point>> inter(const Circle &c1, const Circle &c2) {
	if(!is_inter(c1, c2)) return nullopt;
	ld dis = (c2.c - c1.c).len();
	ld r1 = c1.r, r2 = c2.r;
	ld cosa =
		clamp((r1 * r1 + dis * dis - r2 * r2) / (2 * r1 * dis), -1.0l, 1.0l);
	ld alp = acos(cosa);
	Point v = c2.c - c1.c;
	v = v / v.len() * c1.r;
	return pair{c1.c + v.rotate(alp), c1.c + v.rotate(-alp)};
}
bool is_inter(const Circle &c, const Line &l) {
	ld d = dist(c.c, l);
	return cmp(c.r, d) != -1;
}
optional<pair<Point, Point>> inter(const Circle &c, const Line &l) {
	if(!is_inter(c, l)) return nullopt;
	Point o = c.c;
	Vector v = l.v;
	Point p = l.p - o;
	ld A = v.len2(), B = 2 * dot(p, v), C = p.len2() - c.r * c.r,
	   D = max(B * B - 4 * A * C, 0.0l);
	ld s = sqrt(D);
	ld q = (B > 0 ? -B - s : -B + s) / 2;
	ld t1 = q / A, t2 = C / q;
	Point i1 = l.p + v * t1, i2 = l.p + v * t2;
	return pair{i1, i2};
}
