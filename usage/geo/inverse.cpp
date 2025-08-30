
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;

inline constexpr ld eps = 1e-9l, pi = 3.14159265358979323846264338327950288l, inf = 1e12l;

template<class T, class F> concept binary_func = convertible_to<F, function<bool(T, T)>>;
template<class T1, class T2, class F> requires(binary_func<T1, F> &&convertible_to<T2, T1>) bool chkf(T1 &x, const T2 &y, F &&f) {
	if(f(static_cast<T1>(y), x)) {
		x = static_cast<T1>(y);
		return true;
	}
	return false;
}
template<class T1, class T2> bool chkmin(T1 &x, const T2 &y) {
	return chkf(x, y, less<T1>{});
}
template<class T1, class T2> bool chkmax(T1 &x, const T2 &y) {
	return chkf(x, y, greater<T1>{});
}

int sign(ld a) {
	return (a < -eps) ? -1 : (a > eps) ? 1 : 0;
}
int cmp(ld a, ld b) {
	return sign(a - b);
}
strong_ordering cmpso(ld a, ld b) {
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
	ld len2() const {
		return x * x + y * y;
	}
	ld len() const {
		return sqrt(x * x + y * y);
	}
	// [0, 2*geo_pi)
	ld arg() const {
		ld ret = atan2(y, x);
		int c = cmp(ret, 0);
		return c == 1 ? ret : c == 0 ? 0.0l : ret + 2 * pi;
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
	bool bx = sign(x.y) == 1 || (sign(x.y) == 0 && sign(x.x) == 1),
		 by = sign(y.y) == 1 || (sign(y.y) == 0 && sign(y.x) == 1);
	if(bx != by) return bx;
	return sign(cross(x, y)) == 0;
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
Point inter(const Line &a, const Line &b) {
	if(parallel(a, b))
		throw runtime_error("a and b are parallel");
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
	return sign(cross(ln.v, ln.p - p)) == 0;
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
	return to_left(p - ls.a, p - ls.b) == 0 && sign(dot(p - ls.a, p - ls.b)) == -1;
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
	return to_left(ln1, l2.a) * to_left(ln1, l2.b) == -1 
		&& to_left(ln2, l1.a) * to_left(ln2, l1.b) == -1;
}
ld dist(const Point &p, const Lineseg &ls) {
	if(is_on(p, ls) != 0) {
		return 0.0l;
	}
	if(cmp(dot(p - ls.a, ls.b - ls.a), 0) == -1 ||
	   cmp(dot(p - ls.b, ls.a - ls.b), 0) == -1) {
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
	if(abs(dis) <= eps) {
		return false;
	}
	if(dis > r1 + r2 + eps || dis < abs(r1 - r2) - eps) {
		return false;
	}
	return true;
}
pair<Point, Point> inter(const Circle &c1, const Circle &c2) {
	if(!is_inter(c1, c2))
		throw runtime_error("Circles do not intersect");
	ld dis = (c2.c - c1.c).len();
	ld r1 = c1.r, r2 = c2.r;
	ld cosa = clamp((r1 * r1 + dis * dis - r2 * r2) / (2 * r1 * dis), -1.0l, 1.0l);
	ld alp = acos(cosa);
	Point v = c2.c - c1.c;
	v = v / v.len() * c1.r;
	return { c1.c + v.rotate(alp), c1.c + v.rotate(-alp) };
}
bool is_inter(const Circle &c, const Line &l) {
	ld d = dist(c.c, l);
	return cmp(c.r, d) != -1;
}
pair<Point, Point> inter(const Circle &c, const Line &l) {
	if(!is_inter(c, l))
		throw runtime_error("Circle and line do not intersect");
	Point o = c.c;
	Vector v = l.v;
	Point p = l.p - o;
	ld A = v.len2(), B = 2 * dot(p, v), C = p.len2() - c.r * c.r, D = max(B * B - 4 * A * C, 0.0l);
	ld s = sqrt(D);
	ld q = (B > 0 ? -B - s : -B + s) / 2;
	ld t1 = q / A, t2 = C / q;
	Point i1 = l.p + v * t1, i2 = l.p + v * t2;
	return {i1, i2};
}

// (A invert to C)'s shape, true is circle, false is line
bool inv_shape(const Circle &c, const Circle &a) {
	return cmp(dist(c.c, a.c), a.r) != 0;
}
bool inv_shape(const Circle &c, const Line &l) {
	return sign(cross(c.c - l.p, l.v)) != 0;
}
Point inverse(const Circle &c, const Point &a) {
	Vector v = a - c.c;
	return c.c + v * (c.r * c.r / v.len());
}
Circle invcircle(const Circle &c, const Circle &a) {
	if(!inv_shape(c, a)) throw runtime_error("result type mismatch");
	Vector v = a.c - c.c;
	Point p1 = a.c - v / v.len() * a.r, p2 = a.c + v / v.len() * a.r;
	Point p3 = inverse(c, p1), p4 = inverse(c, p2);
	return Circle((p3 + p4) / 2, dist(p3, p4) / 2);
}
Line invline(const Circle &c, const Circle &a) {
	if(inv_shape(c, a)) throw runtime_error("result type mismatch");
	Vector v = a.c - c.c;
	Point pt = c.c + v * 2;
	Point ip = inverse(c, pt);
	return Line(ip, Vector(-v.y, v.x));
}
Circle invcircle(const Circle &c, const Line &l) {
	if(!inv_shape(c, l)) throw runtime_error("result type mismatch");
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
Line invline(const Circle &c, const Line &l) {
	if(inv_shape(c, l)) throw runtime_error("result type mismatch");
	return l;
}

inline void solve() {
    
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
