#pragma once
#include "geo/basic.h"

struct Convex : public Polygon {
	using Polygon::Polygon;
	array<int, 3> max_triangle() const {
		int m = size();
		if(m < 3) return {-1, -1, -1};
		vector<int> id(m);
		iota(id.begin(), id.end(), 0);
		vector<Point> p = pts;
		if(sign(area()) == -1) {
			reverse(p.begin(), p.end());
			reverse(id.begin(), id.end());
		}
		vector<Point> pts2 = p;
		pts2.insert(pts2.end(), p.begin(), p.end());
		ld rar = -1.0l;
		array<int, 3> ret = {0, 1, 2};
		for(int i = 0; i < m; ++i) {
			int k = i + 2;
			for(int j = i + 1; j < i + m - 1; ++j) {
				while(k + 1 < i + m &&
					  cross(pts2[j] - pts2[i], pts2[k + 1] - pts2[i]) >
						  cross(pts2[j] - pts2[i], pts2[k] - pts2[i]))
					++k;
				ld car = 0.5l * cross(pts2[j] - pts2[i], pts2[k] - pts2[i]);
				if(cmp(car, rar) == 1) {
					rar = car;
					ret = {id[i % m], id[j % m], id[k % m]};
				}
			}
		}
		return ret;
	}
	pair<int, int> farthest() const {
		int m = size();
		if(m == 0) return {-1, -1};
		if(m == 1) return {0, 0};
		if(m == 2) return {0, 1};
		vector<int> id(m);
		iota(id.begin(), id.end(), 0);
		vector<Point> p = pts;
		if(sign(area()) == -1) {
			reverse(p.begin(), p.end());
			reverse(id.begin(), id.end());
		}
		int j = 1;
		ld _dist = 0;
		pair<int, int> ret = {0, 0};
		for(int i = 0; i < m; ++i) {
			int u = (i + 1) % m;
			while(cross(p[i], p[u], p[(j + 1) % m]) > cross(p[i], p[u], p[j]))
				j = (j + 1) % m;
			auto chmax = [&](int k) {
				ld now = (p[k] - p[j]).len2();
				if(cmp(now, _dist) == 1) {
					_dist = now;
					ret = {id[k], id[j]};
				}
			};
			chmax(i);
			chmax(u);
		}
		return ret;
	}
};
bool is_in(const Point &pt, const Convex &cv) {
	if(cv.size() == 1) {
		return pt == cv.pts[0];
	}
	if(cv.size() == 2) {
		return is_on(pt, LineSeg(cv.pts[0], cv.pts[1]));
	}
	auto check = [](const Point &a, const Point &b, const Point &c,
					const Point &p) {
		ld c1 = cross(b - a, p - a), c2 = cross(c - b, p - b),
		   c3 = cross(a - c, p - c);
		return (sign(c1) != -1 && sign(c2) != -1 && sign(c3) != -1) ||
			   (sign(c1) != 1 && sign(c2) != 1 && sign(c3) != 1);
	};
	int n = cv.size();
	Point pivot = cv.pts[0];
	if((sign(cross(cv.pts[1] - pivot, pt - pivot)) == -1) ||
	   (sign(cross(cv.pts[n - 1] - pivot, pt - pivot)) == 1)) {
		return false;
	}
	int l = 1, r = n - 1;
	while(l + 1 < r) {
		int mid = (l + r) >> 1;
		if(sign(cross(cv.pts[mid] - pivot, pt - pivot)) != -1) {
			l = mid;
		} else {
			r = mid;
		}
	}
	int nxt = (l == n - 1) ? 1 : l + 1;
	return check(pivot, cv.pts[l], cv.pts[nxt], pt);
}
opt<pair<Point, Point>> tangent(const Point &pt, const Convex &cv) {
	if(is_in(pt, cv)) return nul;
	int n = cv.size();
	auto peak = [&](int l, int r, bool f) {
		while(l < r - 1) {
			int m = (l + r) / 2;
			if(f ^ (to_left(cv.pts[(m + n - 1) % n] - pt, cv.pts[m] - pt) == 1))
				r = m;
			else l = m;
		}
		return l;
	};
	if(to_left(cv.pts[0] - pt, cv.pts[1] - pt) == 0) {
		int idx =
			peak(2, n, cmp(dist(cv.pts[0], pt), dist(cv.pts[1], pt)) == -1);
		return pair{cv.pts[0], cv.pts[idx]};
	}
	bool al = true, ar = true;
	auto chk = [&](int x) {
		if(x == 1) ar = false;
		if(x == -1) al = false;
	};
	chk(to_left(cv.pts[0] - pt, cv.pts[1] - pt));
	chk(to_left(cv.pts[0] - pt, cv.pts[n - 1] - pt));
	if(al || ar) {
		int id = peak(1, n, al);
		return pair{cv.pts[0], cv.pts[id]};
	}
	int l = 1, r = n;
	while(l < r - 1) {
		int mid = (l + r) / 2;
		if(to_left(cv.pts[0] - pt, cv.pts[mid] - pt) == 1) {
			l = mid;
		} else {
			r = mid;
		}
	}
	bool f = (to_left(cv.pts[0] - pt, cv.pts[1] - pt) == 1);
	int i1 = peak(0, l + 1, f), i2 = peak(l, n, !f);
	return pair{cv.pts[i1], cv.pts[i2]};
}
pair<Point, Point> tangent(const Line &ln, const Convex &cv) {
	int n = cv.size();
	Point dir(-ln.v.y, ln.v.x);
	auto find = [&](bool f) {
		int l = 0, r = n - 1;
		while(r - l > 2) {
			int m1 = l + (r - l) / 3, m2 = r - (r - l) / 3;
			ld dot1 = dot(cv.pts[m1], dir), dot2 = dot(cv.pts[m2], dir);
			if(f ^ (cmp(dot1, dot2) == -1)) {
				r = m2;
			} else {
				l = m1;
			}
		}
		int idx = l;
		ld ret = dot(cv.pts[l], dir);
		for(int i = l; i <= r; ++i) {
			ld now = dot(cv.pts[i], dir);
			if(f ^ (cmp(now, ret) == -1)) {
				idx = i;
				ret = now;
			}
		}
		return idx;
	};
	int i1 = find(true), i2 = find(false);
	return {cv.pts[i1], cv.pts[i2]};
}
Convex minkowski_add(const Convex &a, const Convex &b) {
	int n = a.size(), m = b.size();
	auto cmp = [](const LineSeg &u, const LineSeg &v) {
		return argcmp(u.b - u.a, v.b - v.a);
	};
	vector<LineSeg> e1(n), e2(m), edge(n + m);
	for(int i = 0; i < n; ++i) {
		e1[i] = {a.pts[i], a.pts[(i + 1) % n]};
	}
	for(int i = 0; i < m; ++i) {
		e2[i] = {b.pts[i], b.pts[(i + 1) % m]};
	}
	rotate(e1.begin(), min_element(e1.begin(), e1.end(), cmp), e1.end());
	rotate(e2.begin(), min_element(e2.begin(), e2.end(), cmp), e2.end());
	merge(e1.begin(), e1.end(), e2.begin(), e2.end(), edge.begin(), cmp);
	vector<Point> ret;
	auto bad = [&](const Point &u) {
		int n = ret.size();
		Point b1 = ret.back(), b2 = *prev(ret.end(), 2);
		return to_left(b1 - b2, u - b1) == 0 && sign(dot(b1 - b2, u - b1)) >= 0;
	};
	auto u = e1[0].a + e2[0].a;
	for(const auto &v : edge) {
		while(ret.size() > 1 && bad(u)) {
			ret.pop_back();
		}
		ret.push_back(u);
		u = u + v.b - v.a;
	}
	if(ret.size() > 1 && bad(ret[0])) ret.pop_back();
	return Convex(ret);
}
Convex minkowski_sub(const Convex &a, const Convex &b) {
	Convex nb = b;
	reverse(nb.pts.begin(), nb.pts.end());
	for(auto &pt : nb.pts) {
		pt = Point() - pt;
	}
	return minkowski_add(a, nb);
}
