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

constexpr ld eps = 1e-9;
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
	ld norm2() const {
		return x * x + y * y;
	}
	ld norm() const {
		return sqrt(x * x + y * y);
	}
};

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
