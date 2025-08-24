
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;

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

// Simplified functions for Pick's theorem - no floating point operations needed
// Most geometric operations removed as they're not required for Pick's theorem

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
	// Integer version of angle comparison - avoids floating point calculations
	bool bx = x.y > 0 || (x.y == 0 && x.x > 0);
	bool by = y.y > 0 || (y.y == 0 && y.x > 0);
	if(bx != by) return bx;
	return cross(x, y) == 0;
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

ll point_inside(const Polygon &poly) {
    ll twice_area = poly.twice_area();
    ll border = 0;
    for(int i = 0; i < poly.size(); ++i) {
        int j = (i + 1) % poly.size();
        Vector v = poly.pts[j] - poly.pts[i];
        ll vx = abs(v.x), vy = abs(v.y);
        border += __gcd(vx, vy);
    }
    return (twice_area - border + 2) / 2;
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
