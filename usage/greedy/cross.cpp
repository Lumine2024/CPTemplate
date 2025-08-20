// Standalone C++ file generated from greedy/cross.hpp
// Can be directly submitted to online judges

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;

inline constexpr ll modulo = 998244353, g = 3, inf = 0x3f3f3f3f3f3f3f3f;
inline constexpr int maxn = 100005, infint = 0x3f3f3f3f;
inline constexpr ld eps = 1e-9l, pi = 3.14159265358979323846264338327950288l, infld = 1e12l;

inline ll qpow(ll x, ll n) {
    ll ret = 1;
    for(; n != 0; n >>= 1, x = x * x % modulo) {
        if(n & 1) ret = ret * x % modulo;
    }
    return ret;
}

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

// === geo/basic.hpp (Point and cmp needed for cross) ===

using ld = long double;
int sign(ld a) {
	return (a < -eps) ? -1 : (a > eps) ? 1 : 0;
}
int cmp(ld a, ld b) {
	return sign(a - b);
}

struct Point {
	ld x, y;
	Point(ld _x = 0, ld _y = 0) : x(_x), y(_y) {}
	Point operator+(const Point &p) const {
		return Point(x + p.x, y + p.y);
	}
	Point operator-(const Point &p) const {
		return Point(x - p.x, y - p.y);
	}
	Point operator*(ld k) const {
		return Point(k * x, k * y);
	}
	Point operator/(ld k) const {
		return Point(x / k, y / k);
	}
	bool operator==(const Point &p) const {
		return cmp(x, p.x) == 0 && cmp(y, p.y) == 0;
	}
	bool operator<(const Point &p) const {
		return cmp(x, p.x) < 0 || (cmp(x, p.x) == 0 && cmp(y, p.y) < 0);
	}
	Point perp() const {
		return Point(-y, x);
	}
	ld dot(const Point &p) const {
		return x * p.x + y * p.y;
	}
	ld cross(const Point &p) const {
		return x * p.y - y * p.x;
	}
	ld norm() const {
		return x * x + y * y;
	}
	ld norm2() const {
		return sqrt(norm());
	}
};

using Vector = Point;

// === greedy/cross.hpp ===

bool cross_all(const vector<Point> &points) {
	bool okx = true, oky = true;
	ld xb = -1, yb = -1;
	for(auto [x, y] : points) {
		if(cmp(x, points[0].x) != 0) {
			if(yb == -1) {
				yb = y;
			} else if(cmp(yb, y) != 0) {
				okx = false;
			}
		}
		if(cmp(y, points[0].y) != 0) {
			if(xb == -1) {
				xb = x;
			} else if(cmp(xb, x) != 0) {
				oky = false;
			}
		}
	}
	return okx || oky;
}

// Example usage:
inline void solve() {
    // Add your solution code here using the template above
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
