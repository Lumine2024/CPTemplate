#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using cd = complex<ld>;

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

constexpr ld eps = 2e-10l, pi = 3.14159265358979323846264338327950288l;
int sign(ld x) {
	return x > eps ? 1 : x < -eps ? -1 : 0;
}
int cmp(ld x, ld y) {
	return sign(x - y);
}
strong_ordering cmpso(ld a, ld b) {
	return cmp(a, b) <=> 0;
}

struct Point {
	ld x, y, z;
	Point() : x(0), y(0), z(0) {}
	Point(ld _x, ld _y, ld _z) : x(_x), y(_y), z(_z) {}
	Point operator+(const Point &p) const { return Point(x + p.x, y + p.y, z + p.z); }
	Point operator-(const Point &p) const { return Point(x - p.x, y - p.y, z - p.z); }
	Point operator*(ld u) const { return Point(x * u, y * u, z * u); }
	friend Point operator*(ld u, const Point &p) { return p * u; }
	Point operator/(ld u) const { return Point(x / u, y / u, z / u); }
	ld len() const { return sqrt(x * x + y * y + z * z); }
	ld len2() const { return x * x + y * y + z * z; }
	bool operator==(const Point &p) const { return cmp(x, p.x) == 0 && cmp(y, p.y) == 0 && cmp(z, p.z) == 0; }
};
using Vector = Point;
ld dot(const Vector &a, const Vector &b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}
Vector cross(const Vector &a, const Vector &b) {
	return Vector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}
Vector cross(const Point &o, const Point &a, const Point &b) {
	return cross(a - o, b - o);
}
ld mix_prod(const Vector &a, const Vector &b, const Vector &c) {
	return dot(cross(a, b), c);
}
ld dist(const Point &a, const Point &b) {
	return (a - b).len();
}
bool same_plane(const Point &a, const Point &b, const Point &c, const Point &d) {
	return sign(mix_prod(b - a, c - a, d - a)) == 0;
}
bool parallel(const Vector &a, const Vector &b) {
	Vector v = cross(a, b);
	return sign(v.len()) == 0;
}
bool same_line(const Point &a, const Point &b, const Point &c) {
	return parallel(b - a, c - a);
}
ld operator/(const Vector &a, const Vector &b) {
	if(!parallel(a, b)) throw runtime_error("a and b don't parallel");
	return sign(b.x) == 0 ? a.y / b.y : a.x / b.x;
}
Point proj(const Point &p, const Vector &base) {
	if(sign(base.len2()) == 0) return Point(0, 0, 0);
	ld t = dot(p, base) / base.len2();
	return base * t;
}

struct Line {
	Point p, v;
	Line() {}
	Line(const Point &_p, const Vector &_v) : p(_p), v(_v) {}
};
bool parallel(const Line &a, const Line &b) {
	return parallel(a.v, b.v);
}
bool same_plane(const Line &a, const Line &b) {
	return same_plane(a.p, a.p + a.v, b.p, b.p + b.v);
}
bool is_inter(const Line &a, const Line &b) {
	return same_plane(a, b) && !parallel(a, b);
}
Point inter(const Line &a, const Line &b) {
	if(!is_inter(a, b)) throw runtime_error("a and b don't intersect");
	Vector w = b.p - a.p, v1v2 = cross(a.v, b.v);
	Vector wv2 = cross(w, b.v);
	ld den = v1v2.len2();
	ld t = dot(wv2, v1v2) / den;
	return a.p + a.v * t;
}

struct Plane {
	Point p, norm;
	Plane() {}
	Plane(const Point &_p, const Vector &_n) : p(_p), norm(_n) {}
	Plane(const Point &a, const Point &b, const Point &c) : p(a), norm(cross(b - a, c - a)) {}
};
bool parallel(const Plane &a, const Plane &b) {
	return parallel(a.norm, b.norm);
}

inline void solve() {
	
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout << setprecision(9) << fixed;
	int t = 1;
	// cin >> t;
	for(int i = 0; i < t; ++i) {
		solve();
	}
	return 0;
}