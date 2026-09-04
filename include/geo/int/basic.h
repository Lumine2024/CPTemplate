#pragma once
#include "common.h"

struct PointInt {
	ll x, y;
	PointInt() : x(0), y(0) {}
	PointInt(ll _x, ll _y) : x(_x), y(_y) {}
	PointInt operator+(const PointInt &p) const {
		return PointInt(x + p.x, y + p.y);
	}
	PointInt operator-(const PointInt &p) const {
		return PointInt(x - p.x, y - p.y);
	}
	PointInt operator*(ll z) const {
		return PointInt(z * x, z * y);
	}
	friend PointInt operator*(ll z, const PointInt &p) {
		return p * z;
	}
	bool operator==(const PointInt &p) const {
		return x == p.x && y == p.y;
	}
	ll len2() const {
		return x * x + y * y;
	}
	ll &operator[](int i) {
		return i == 0 ? x : y;
	}
	ll operator[](int i) const {
		return i == 0 ? x : y;
	}
};
ll dot(const PointInt &x, const PointInt &y) {
	return x.x * y.x + x.y * y.y;
}
ll cross(const PointInt &x, const PointInt &y) {
	return x.x * y.y - x.y * y.x;
}
ll cross(const PointInt &o, const PointInt &a, const PointInt &b) {
	return cross(a - o, b - o);
}
bool argcmp(const PointInt &x, const PointInt &y) {
	bool bx = x.y > 0 || (x.y == 0 && x.x > 0),
		 by = y.y > 0 || (y.y == 0 && y.x > 0);
	if(bx != by) return bx;
	return cross(x, y) > 0;
}
ll dist2(const PointInt &a, const PointInt &b) {
	return (a - b).len2();
}
int to_left(const PointInt &a, const PointInt &b) {
	ll c = cross(a, b);
	return c > 0 ? 1 : c < 0 ? -1 : 0;
}
int to_left(const PointInt &a, const PointInt &b, const PointInt &c) {
	ll cr = cross(a, b, c);
	return cr > 0 ? 1 : cr < 0 ? -1 : 0;
}

struct LineInt {
	PointInt p, v;
	LineInt() {}
	LineInt(const PointInt &_p, const PointInt &_v) : p(_p), v(_v) {}
};
int to_left(const LineInt &ln, const PointInt &p) {
	return to_left(ln.v, p - ln.p);
}
bool parallel(const LineInt &l1, const LineInt &l2) {
	return cross(l1.v, l2.v) == 0;
}
int is_inter(const LineInt &l1, const LineInt &l2) {
	return parallel(l1, l2) ? 0 : 1;
}
bool is_on(const PointInt &p, const LineInt &ln) {
	return cross(ln.v, ln.p - p) == 0;
}

struct LineSegInt {
	PointInt a, b;
	LineSegInt() {}
	LineSegInt(const PointInt &_a, const PointInt &_b) : a(_a), b(_b) {}
};
int is_on(const PointInt &p, const LineSegInt &ls) {
	if(p == ls.a || p == ls.b) return 2;
	return to_left(p - ls.a, p - ls.b) == 0 && dot(p - ls.a, p - ls.b) < 0;
}
int is_inter(const LineInt &ln, const LineSegInt &ls) {
	int a = to_left(ln, ls.a), b = to_left(ln, ls.b);
	if(a == 0 || b == 0) return 2;
	return a == b ? 0 : 1;
}
int is_inter(const LineSegInt &l1, const LineSegInt &l2) {
	if(is_on(l1.a, l2) || is_on(l1.b, l2) || is_on(l2.a, l1) || is_on(l2.b, l1))
		return 2;
	LineInt ln1(l1.a, l1.b - l1.a), ln2(l2.a, l2.b - l2.a);
	return to_left(ln1, l2.a) * to_left(ln1, l2.b) == -1 &&
		   to_left(ln2, l1.a) * to_left(ln2, l1.b) == -1;
}
