#include "basic.h"

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
	auto check = [](const Point &a, const Point &b, const Point &c,
					const Point &p) {
		ld c1 = cross(b - a, p - a), c2 = cross(c - b, p - b),
		   c3 = cross(a - c, p - c);
		return (sign(c1) != -1 && sign(c2) != -1 && sign(c3) != -1) ||
			   (sign(c1) != 1 && sign(c2) != 1 && sign(c3) != 1);
	};
	int n = convex.size();
	Point pivot = convex.pts[0];
	if((sign(cross(convex.pts[1] - pivot, pt - pivot)) == -1) ||
	   (sign(cross(convex.pts[n - 1] - pivot, pt - pivot)) == 1)) {
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
optional<pair<Point, Point>> tangent(const Point &pt, const Convex &convex) {
	if(is_in(pt, convex)) return nullopt;
	int n = convex.size();
	auto peak = [&](int l, int r, bool find_r) {
		while(l < r - 1) {
			int mid = (l + r) / 2;
			if(find_r ^ (to_left(convex.pts[(mid + n - 1) % n] - pt,
								 convex.pts[mid] - pt) == 1))
				r = mid;
			else l = mid;
		}
		return l;
	};
	if(to_left(convex.pts[0] - pt, convex.pts[1] - pt) == 0) {
		int idx = peak(
			2, n, cmp(dist(convex.pts[0], pt), dist(convex.pts[1], pt)) == -1);
		return pair{convex.pts[0], convex.pts[idx]};
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
		return pair{convex.pts[0], convex.pts[idx]};
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
	return pair{convex.pts[i1], convex.pts[i2]};
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
	return {convex.pts[i1], convex.pts[i2]};
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
