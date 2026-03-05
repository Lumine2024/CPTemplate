#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;

template<class T1, class T2, class F> bool chkf(T1 &x, const T2 &y, F &&f) {
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

struct Point {
	ll x, y;
	Point() : x(0), y(0) {}
	Point(ll _x, ll _y) : x(_x), y(_y) {}
	Point operator+(const Point &p) const {
		return Point(x + p.x, y + p.y);
	}
	Point operator-(const Point &p) const {
		return Point(x - p.x, y - p.y);
	}
	Point operator*(ll z) const {
		return Point(z * x, z * y);
	}
	friend Point operator*(ll z, const Point &p) {
		return p * z;
	}
	bool operator==(const Point &p) const {
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
using Vector = Point;
ll dot(const Vector &x, const Vector &y) {
	return x.x * y.x + x.y * y.y;
}
ll cross(const Vector &x, const Vector &y) {
	return x.x * y.y - x.y * y.x;
}
ll cross(const Point &o, const Point &a, const Point &b) {
	return cross(a - o, b - o);
}
bool argcmp(const Point &x, const Point &y) {
	bool bx = x.y > 0 || (x.y == 0 && x.x > 0),
		 by = y.y > 0 || (y.y == 0 && y.x > 0);
	if(bx != by) return bx;
	return cross(x, y) > 0;
}
ll dist2(const Point &a, const Point &b) {
	return (a - b).len2();
}
int to_left(const Vector &a, const Vector &b) {
	ll c = cross(a, b);
	return c > 0 ? 1 : c < 0 ? -1 : 0;
}
int to_left(const Point &a, const Point &b, const Point &c) {
	ll cr = cross(a, b, c);
	return cr > 0 ? 1 : cr < 0 ? -1 : 0;
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
	return cross(l1.v, l2.v) == 0;
}
int is_inter(const Line &l1, const Line &l2) {
	return parallel(l1, l2) ? 0 : 1;
}
bool is_on(const Point &p, const Line &ln) {
	return cross(ln.v, ln.p - p) == 0;
}

struct Polygon {
	vector<Point> pts;
	Polygon() {}
	Polygon(const vector<Point> &p) : pts(p) {}
	ll twice_area() const {
		ll ret = 0;
		for(int i = 0; i < pts.size(); ++i) {
			ret += cross(pts[i], pts[(i + 1) % pts.size()]);
		}
		return abs(ret);
	}
	int size() const {
		return pts.size();
	}
};

ll points_inside(const Polygon &poly) {
	ll twos = poly.twice_area();
	ll border = 0;
	for(int i = 0; i < poly.size(); ++i) {
		int j = (i + 1) % poly.size();
		Vector v = poly.pts[j] - poly.pts[i];
		border += gcd(abs(v.x), abs(v.y));
	}
	return (twos - border + 2) / 2;
}

inline void solve() {}

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
