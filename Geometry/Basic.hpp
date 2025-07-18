#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

using ld = long double;
constexpr ld eps = 1e-9;
int sign(ld a) {
	return (a < -eps) ? -1 : (a > eps) ? 1 : 0;
}
int cmp(ld a, ld b) {
	return sign(a - b);
}
constexpr ld pi = 3.1415926535897932384626l;
constexpr ld inf = 1e12l;

struct Point {
	ld x, y;
	Point() : x(0.0l), y(0.0l) {}
	Point(ld _x, ld _y) : x(_x), y(_y) {}
	Point(const complex<ld> &cd) : x(cd.real()), y(cd.imag()) {}
	operator complex<ld>() const {
		return complex<ld>(x, y);
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
	ld len() const {
		return sqrt(x * x + y * y);
	}
	// [0, 2pi)
	ld arg() const {
		ld ret = atan2(y, x);
		int c = cmp(ret, 0);
		return c == 1 ? ret : c == 0 ? 0.0l : ret + 2 * pi;
	}
	int quad() const {
		int cx = cmp(x, 0), cy = cmp(y, 0);
		return (cx == 0 && cy == 0) ? 0 : (cx == 1 && cy == 0) ? 1 : (cx == 1 && cy == 1) ? 2 : (cx == 0 && cy == 1) ? 3 : (cx == -1 && cy == 1) ? 4 : (cx == -1 && cy == 0) ? 5 : (cx == -1 && cy == -1) ? 6 : (cx == 0 && cy == -1) ? 7 : 8;
	}
	Point rotate(ld a) const {
		return Point(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
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
	int qx = x.quad(), qy = y.quad();
	if(qx != qy)
		return qx < qy;
	return cmp(cross(x, y), 0.0l) == 1;
}
ld dist(const Point &x, const Point &y) {
	return (x - y).len();
}
int to_left(const Vector &a, const Vector &b) {
	return sign(cross(a, b));
}
int to_left(const Point &a, const Point &b, const Point &c) {
	return sign(cross(a, b, c));
}

struct Line {
	Point p, v;
	Line() {}
	Line(const Point &_p, const Vector &_v) : p(_p), v(_v) {}
};
int to_left(const Line &ln, const Point &p) {
	return to_left(ln.v, p - ln.p);
}
bool parallel(const Line &l1, const Line &l2) {
	return cmp(cross(l1.v, l2.v), 0.0l) == 0;
}
int is_inter(const Line &l1, const Line &l2) {
	return parallel(l1, l2) ? 0 : 1;
}
Point inter(const Line &a, const Line &b) {
	if(parallel(a, b))
		throw invalid_argument("a and b are parallel");
	Vector v = a.v * (cross(b.v, a.p - b.p) / cross(a.v, b.v));
	return a.p + v;
}
ld dist(const Point &p, const Line &ln) {
	return abs(cross(ln.v, p - ln.p)) / ln.v.len();
}
ld dist(const Line &l1, const Line &l2) {
	if(!parallel(l1, l2)) {
		return 0;
	}
	return dist(l1.p, l2);
}
Point proj(const Point &p, const Line &ln) {
	Vector v = ln.v * (dot(ln.v, p - ln.p) / (dot(ln.v, ln.v)));
	return ln.p + v;
}
bool is_on(const Point &p, const Line &ln) {
	return cmp(cross(ln.v, ln.p - p), 0.0l) == 0;
}

struct Lineseg {
	Point a, b;
	Lineseg() {}
	Lineseg(const Point &_a, const Point &_b) : a(_a), b(_b) {}
	ld len() const {
		return (b - a).len();
	}
};
int is_on(const Point &p, const Lineseg &ls) {
	if(p == ls.a || p == ls.b) {
		return 2;
	}
	return to_left(p - ls.a, p - ls.b) == 0 && cmp(dot(p - ls.a, p - ls.b), 0) == -1;
}
int is_inter(const Line &ln, const Lineseg &ls) {
	int a = to_left(ln, ls.a), b = to_left(ln, ls.b);
	if(a == 0 || b == 0) {
		return 2;
	}
	return a == b ? 0 : 1;
}
int is_inter(const Lineseg &l1, const Lineseg &l2) {
	if(is_on(l1.a, l2) || is_on(l1.b, l2) || is_on(l2.a, l1) || is_on(l2.b, l1)) {
		return 2;
	}
	Line ln1(l1.a, l1.b - l1.a), ln2(l2.a, l2.b - l2.a);
	return to_left(ln1, l2.a) * to_left(ln1, l2.b) == -1 && to_left(ln2, l1.a) * to_left(ln2, l1.b) == -1;
}
ld dist(const Point &p, const Lineseg &ls) {
	if(is_on(p, ls) != 0) {
		return 0.0l;
	}
	if(cmp(dot(p - ls.a, ls.b - ls.a), 0) == -1 || cmp(dot(p - ls.b, ls.a - ls.b), 0) == -1) {
		return min(dist(p, ls.a), dist(p, ls.b));
	}
	Line l(ls.a, ls.b - ls.a);
	return dist(p, l);
}

struct Polygon {
	vector<Point> pts;
	Polygon() {}
	Polygon(const vector<Point> &p) : pts(p) {}
	Polygon(const vector<Line> &l) {
		pts.reserve(l.size());
		for(int i = 0; i < l.size(); ++i) {
			pts.emplace_back(inter(l[i], l[(i + 1) % l.size()]));
		}
	}
	ld area() const {
		ld ret = 0.0l;
		for(int i = 0; i < pts.size(); ++i) {
			ret += cross(pts[i], pts[(i + 1) % pts.size()]);
		}
		return ret / 2.0l;
	}
	ld circ() const {
		ld ret = 0.0l;
		for(int i = 0; i < pts.size(); ++i) {
			ret += (pts[i] - pts[(i + 1) % pts.size()]).len();
		}
		return ret;
	}
};