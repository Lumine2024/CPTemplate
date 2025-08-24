
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;

inline constexpr ll inf = 0x3f3f3f3f3f3f3f3f;
inline constexpr ld eps = 1e-9l, pi = 3.14159265358979323846264338327950288l, infld = 1e12l;

template<class T, class F> bool chkf(T &x, const T &y, F &&f) {
    if(f(y, x)) {
        x = y;
        return true;
    }
    return false;
}
template<class T> bool chkmin(T &x, const T &y) {
    return chkf(x, y, less{});
}
template<class T> bool chkmax(T &x, const T &y) {
    return chkf(x, y, greater{});
}


using ld = long double;
int sign(ld a) {
	return (a < -eps) ? -1 : (a > eps) ? 1 : 0;
}
int cmp(ld a, ld b) {
	return sign(a - b);
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
	ld cosa = min(max(dot(a, b) / (a.len() * b.len()), -1.0l), 1.0l);
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
	return cmp(cross(l1.v, l2.v), 0.0l) == 0;
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
	ld cosa = ((r1 * r1 + dis * dis - r2 * r2) / (2 * r1 * dis));
	cosa = min(max(cosa, -1.0l), 1.0l);
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

struct Convex : public Polygon {
	using Polygon::Polygon;
	// todo
};
bool is_in(const Point &pt, const Convex &convex) {
	if(convex.size() == 1) {
		return pt == convex.pts[0];
	}
	if(convex.size() == 2) {
		return is_on(pt, Lineseg(convex.pts[0], convex.pts[1]));
	}
	auto check = [](const Point &a, const Point &b, const Point &c, const Point &p) {
		ld c1 = cross(b - a, p - a), c2 = cross(c - b, p - b), c3 = cross(a - c, p - c);
		return (sign(c1) != -1 && sign(c2) != -1 && sign(c3) != -1) 
			|| (sign(c1) != 1 && sign(c2) != 1 && sign(c3) != 1);
	};
	int n = convex.size();
	Point pivot = convex.pts[0];
	if((sign(cross(convex.pts[1] - pivot, pt - pivot)) == -1) 
	|| (sign(cross(convex.pts[n - 1] - pivot, pt - pivot)) == 1)) {
		return false;
	}
	int l = 1, r = n - 1;
	while(l + 1 < r) {
		int mid = (l + r) >> 1;
		if(sign(cross(convex.pts[mid] - pivot, pt - pivot)) != -1) {
			l = mid;
		} else {
			r = mid;
		}
	}
	int nxt = (l == n - 1) ? 1 : l + 1;
	return check(pivot, convex.pts[l], convex.pts[nxt], pt);
}
pair<Point, Point> tangent(const Point &pt, const Convex &convex) {
	if(is_in(pt, convex)) throw runtime_error("pt is in the convex");
	int n = convex.size();
	auto peak = [&](int l, int r, bool find_r) {
		while(l < r - 1) {
			int mid = (l + r) / 2;
			if(find_r ^ (to_left(convex.pts[(mid + n - 1) % n] - pt, convex.pts[mid] - pt) == 1)) {
				r = mid;
			} else {
				l = mid;
			}
		}
		return l;
	};
	if(to_left(convex.pts[0] - pt, convex.pts[1] - pt) == 0) {
		int idx = peak(2, n, cmp(dist(convex.pts[0], pt), dist(convex.pts[1], pt)) == -1);
		return { convex.pts[0], convex.pts[idx] };
	}
	bool all_left = true, all_right = true;
	auto chk = [&](int x) {
		if(x == 1) all_right = false;
		if(x == -1) all_left = false;
	};
	chk(to_left(convex.pts[0] - pt, convex.pts[1] - pt));
	chk(to_left(convex.pts[0] - pt, convex.pts[n - 1] - pt));
	if(all_left || all_right) {
		int idx = peak(1, n, all_left);
		return { convex.pts[0], convex.pts[idx] };
	}
	int l = 1, r = n;
	while(l < r - 1) {
		int mid = (l + r) / 2;
		if(to_left(convex.pts[0] - pt, convex.pts[mid] - pt) == 1) {
			l = mid;
		} else {
			r = mid;
		}
	}
	int split = l;
	bool flag = (to_left(convex.pts[0] - pt, convex.pts[1] - pt) == 1);
	int i1 = peak(0, split + 1, flag), i2 = peak(split, n, !flag);
	return { convex.pts[i1], convex.pts[i2] };
}
pair<Point, Point> tangent(const Line &ln, const Convex &convex) {
	int n = convex.size();
	Vector dir(-ln.v.y, ln.v.x);
	auto find = [&](bool flag) {
		int l = 0, r = n - 1;
		while(r - l > 2) {
			int m1 = l + (r - l) / 3, m2 = r - (r - l) / 3;
			ld dot1 = dot(convex.pts[m1], dir), dot2 = dot(convex.pts[m2], dir);
			if(flag ^ (cmp(dot1, dot2) == -1)) {
				r = m2;
			} else {
				l = m1;
			}
		}
		int idx = l;
		ld ret = dot(convex.pts[l], dir);
		for(int i = l; i <= r; ++i) {
			ld now = dot(convex.pts[i], dir);
			if(flag ^ (cmp(now, ret) == -1)) {
				idx = i;
				ret = now;
			}
		}
		return idx;
	};
	int i1 = find(true), i2 = find(false);
	return { convex.pts[i1], convex.pts[i2] };
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
