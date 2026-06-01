#pragma once
#include "common.h"

template<class T>
using opt = optional<T>;
constexpr auto nul = nullopt;

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
		return hypot(x, y);
	}
	Point norm() const {
		if(sign(len()) == 0) return Point();
		return (*this) * (1.0l / len());
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
ld dot(const Point &x, const Point &y) {
	return x.x * y.x + x.y * y.y;
}
ld cross(const Point &x, const Point &y) {
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
int to_left(const Point &a, const Point &b) {
	return sign(cross(a, b));
}
int to_left(const Point &o, const Point &a, const Point &b) {
	return to_left(a - o, b - o);
}
ld angle(const Point &a, const Point &b) {
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
	Line(const Point &_p, const Point &_v) : p(_p), v(_v) {}
	ld at(ld x) const {
		if(sign(v.x) == 0) return -inf;
		ld dx = x - p.x;
		ld rt = dx / v.x;
		return (p + rt * v).y;
	}
};
int to_left(const Line &ln, const Point &p) {
	if(p == ln.p) return 0;
	return to_left(ln.v, p - ln.p);
}
bool parallel(const Line &l1, const Line &l2) {
	return sign(cross(l1.v, l2.v)) == 0;
}
int is_inter(const Line &l1, const Line &l2) {
	return parallel(l1, l2) ? 0 : 1;
}
opt<Point> inter(const Line &a, const Line &b) {
	if(parallel(a, b)) return nul;
	Point v = a.v * (cross(b.v, a.p - b.p) / cross(a.v, b.v));
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
	auto lv = ln.v.norm(), lp = ln.p;
	Point v = lv * (dot(lv, p - lp) / lv.len2());
	return lp + v;
}
bool is_on(const Point &p, const Line &ln) {
	return sign(cross(ln.v, ln.p - p)) == 0;
}
Line midperp(const Point &a, const Point &b) {
	Point mid = (a + b) / 2;
	Point to(-(b - a).y, (b - a).x);
	return Line(mid, to);
}

struct LineSeg {
	Point a, b;
	LineSeg() {}
	LineSeg(const Point &_a, const Point &_b) : a(_a), b(_b) {}
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
int is_on(const Point &p, const LineSeg &ls) {
	if(p == ls.a || p == ls.b) return 2;
	return to_left(p - ls.a, p - ls.b) == 0 &&
		   sign(dot(p - ls.a, p - ls.b)) == -1;
}
int is_inter(const Line &ln, const LineSeg &ls) {
	int a = to_left(ln, ls.a), b = to_left(ln, ls.b);
	if(a == 0 || b == 0) return 2;
	return a == b ? 0 : 1;
}
opt<Point> inter(const Line &ln, const LineSeg &ls) {
	if(!is_inter(ln, ls)) return nul;
	return inter(ln, Line(ls.a, ls.b - ls.a));
}
int is_inter(const LineSeg &l1, const LineSeg &l2) {
	if(is_on(l1.a, l2) || is_on(l1.b, l2) || is_on(l2.a, l1) || is_on(l2.b, l1))
		return 2;
	Line ln1(l1.a, l1.b - l1.a), ln2(l2.a, l2.b - l2.a);
	return to_left(ln1, l2.a) * to_left(ln1, l2.b) == -1 &&
		   to_left(ln2, l1.a) * to_left(ln2, l1.b) == -1;
}
ld dist(const Point &p, const LineSeg &ls) {
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
		for(int i = 0; i < (int)l.size(); ++i)
			pts.emplace_back(*inter(l[i], l[(i + 1) % l.size()]));
	}
	ld area() const {
		ld ret = 0.0l;
		for(int i = 0; i < (int)pts.size(); ++i)
			ret += cross(pts[i], pts[(i + 1) % pts.size()]);
		return ret / 2.0l;
	}
	ld circ() const {
		ld ret = 0.0l;
		for(int i = 0; i < (int)pts.size(); ++i)
			ret += dist(pts[i], pts[(i + 1) % pts.size()]);
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
	ld d = (c2.c - c1.c).len();
	ld r1 = c1.r, r2 = c2.r;
	if(abs(d) <= eps) return false;
	if(d > r1 + r2 + eps || d < abs(r1 - r2) - eps) return false;
	return true;
}
opt<pair<Point, Point>> inter(const Circle &c1, const Circle &c2) {
	if(!is_inter(c1, c2)) return nul;
	ld d = dist(c2.c, c1.c);
	ld r1 = c1.r, r2 = c2.r;
	ld ca = clamp((r1 * r1 + d * d - r2 * r2) / (2 * r1 * d), -1.0l, 1.0l);
	ld a = acos(ca);
	Point v = c2.c - c1.c;
	v = v / v.len() * c1.r;
	return pair{c1.c + v.rotate(a), c1.c + v.rotate(-a)};
}
bool is_inter(const Circle &c, const Line &l) {
	ld d = dist(c.c, l);
	return cmp(c.r, d) != -1;
}
opt<pair<Point, Point>> inter(const Circle &c, const Line &l) {
	if(!is_inter(c, l)) return nul;
	Point h = proj(c.c, l);
	ld d2 = dist2(c.c, h);
	ld rem = max(c.r * c.r - d2, 0.0l);
	Point dir = l.v / l.v.len();
	ld t = sqrt(rem);
	Point p1 = h + dir * t;
	Point p2 = h - dir * t;
	return pair{p1, p2};
}
