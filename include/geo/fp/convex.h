#pragma once
#include "geo/fp/basic.h"

array<int, 3> convex_max_triangle(const vector<Point> &cv) {
	int m = cv.size();
	if(m < 3) return {-1, -1, -1};
	auto get = [&](int i) { return cv[i % m]; };
	ld max_area = -1.0l;
	array<int, 3> ret = {0, 1, 2};
	for(int i = 0; i < m; ++i) {
		int k = i + 2;
		for(int j = i + 1; j < i + m - 1; ++j) {
			while(k + 1 < i + m && cross(get(j) - get(i), get(k + 1) - get(i)) >
									   cross(get(j) - get(i), get(k) - get(i)))
				++k;
			ld area = 0.5l * cross(get(j) - get(i), get(k) - get(i));
			if(cmp(area, max_area) == 1) {
				max_area = area;
				ret = {i, j % m, k % m};
			}
		}
	}
	return ret;
}

pair<int, int> convex_farthest(const vector<Point> &cv) {
	int m = cv.size();
	if(m == 0) return {-1, -1};
	if(m == 1) return {0, 0};
	if(m == 2) return {0, 1};
	int j = 1;
	ld max_dist = 0;
	pair<int, int> ret = {0, 0};
	for(int i = 0; i < m; ++i) {
		int u = (i + 1) % m;
		while(cross(cv[i], cv[u], cv[(j + 1) % m]) > cross(cv[i], cv[u], cv[j]))
			j = (j + 1) % m;
		auto chmax = [&](int k) {
			ld now = (cv[k] - cv[j]).len2();
			if(cmp(now, max_dist) == 1) {
				max_dist = now;
				ret = {k, j};
			}
		};
		chmax(i);
		chmax(u);
	}
	return ret;
}

bool is_in_convex(const Point &pt, const vector<Point> &cv) {
	if(cv.empty()) return false;
	if(cv.size() == 1) return pt == cv[0];
	if(cv.size() == 2) return is_on(pt, LineSeg(cv[0], cv[1]));
	auto check = [](const Point &a, const Point &b, const Point &c,
					const Point &p) {
		ld c1 = cross(b - a, p - a), c2 = cross(c - b, p - b),
		   c3 = cross(a - c, p - c);
		return (sign(c1) != -1 && sign(c2) != -1 && sign(c3) != -1) ||
			   (sign(c1) != 1 && sign(c2) != 1 && sign(c3) != 1);
	};
	int n = cv.size();
	Point pivot = cv[0];
	if(sign(cross(cv[1] - pivot, pt - pivot)) == -1 ||
	   sign(cross(cv[n - 1] - pivot, pt - pivot)) == 1)
		return false;
	int l = 1, r = n - 1;
	while(l + 1 < r) {
		int mid = (l + r) >> 1;
		if(sign(cross(cv[mid] - pivot, pt - pivot)) != -1) l = mid;
		else r = mid;
	}
	int nxt = (l == n - 1) ? 1 : l + 1;
	return check(pivot, cv[l], cv[nxt], pt);
}

opt<pair<Point, Point>> convex_tangent(const Point &pt,
									   const vector<Point> &cv) {
	if(is_in_convex(pt, cv)) return nul;
	int n = cv.size();
	auto peak = [&](int l, int r, bool f) {
		while(l < r - 1) {
			int m = (l + r) / 2;
			if(f ^ (to_left(cv[(m + n - 1) % n] - pt, cv[m] - pt) == 1)) r = m;
			else l = m;
		}
		return l;
	};
	if(to_left(cv[0] - pt, cv[1] - pt) == 0) {
		int idx = peak(2, n, cmp(dist(cv[0], pt), dist(cv[1], pt)) == -1);
		return pair{cv[0], cv[idx]};
	}
	bool al = true, ar = true;
	auto chk = [&](int x) {
		if(x == 1) ar = false;
		if(x == -1) al = false;
	};
	chk(to_left(cv[0] - pt, cv[1] - pt));
	chk(to_left(cv[0] - pt, cv[n - 1] - pt));
	if(al || ar) {
		int id = peak(1, n, al);
		return pair{cv[0], cv[id]};
	}
	int l = 1, r = n;
	while(l < r - 1) {
		int mid = (l + r) / 2;
		if(to_left(cv[0] - pt, cv[mid] - pt) == 1) l = mid;
		else r = mid;
	}
	bool f = to_left(cv[0] - pt, cv[1] - pt) == 1;
	int i1 = peak(0, l + 1, f), i2 = peak(l, n, !f);
	return pair{cv[i1], cv[i2]};
}

pair<Point, Point> convex_tangent(const Line &ln, const vector<Point> &cv) {
	int n = cv.size();
	Point dir(-ln.v.y, ln.v.x);
	auto find = [&](bool f) {
		int l = 0, r = n - 1;
		while(r - l > 2) {
			int m1 = l + (r - l) / 3, m2 = r - (r - l) / 3;
			ld dot1 = dot(cv[m1], dir), dot2 = dot(cv[m2], dir);
			if(f ^ (cmp(dot1, dot2) == -1)) r = m2;
			else l = m1;
		}
		int idx = l;
		ld ret = dot(cv[l], dir);
		for(int i = l; i <= r; ++i) {
			ld now = dot(cv[i], dir);
			if(f ^ (cmp(now, ret) == -1)) {
				idx = i;
				ret = now;
			}
		}
		return idx;
	};
	int i1 = find(true), i2 = find(false);
	return {cv[i1], cv[i2]};
}

vector<Point> minkowski_add(const vector<Point> &a, const vector<Point> &b) {
	int n = a.size(), m = b.size();
	auto cmp = [](const LineSeg &u, const LineSeg &v) {
		return argcmp(u.b - u.a, v.b - v.a);
	};
	vector<LineSeg> e1(n), e2(m), edge(n + m);
	for(int i = 0; i < n; ++i) e1[i] = {a[i], a[(i + 1) % n]};
	for(int i = 0; i < m; ++i) e2[i] = {b[i], b[(i + 1) % m]};
	rotate(e1.begin(), min_element(e1.begin(), e1.end(), cmp), e1.end());
	rotate(e2.begin(), min_element(e2.begin(), e2.end(), cmp), e2.end());
	merge(e1.begin(), e1.end(), e2.begin(), e2.end(), edge.begin(), cmp);
	vector<Point> ret;
	auto bad = [&](const Point &u) {
		Point b1 = ret.back(), b2 = *prev(ret.end(), 2);
		return to_left(b1 - b2, u - b1) == 0 && sign(dot(b1 - b2, u - b1)) >= 0;
	};
	auto u = e1[0].a + e2[0].a;
	for(const auto &v : edge) {
		while(ret.size() > 1 && bad(u)) ret.pop_back();
		ret.push_back(u);
		u = u + v.b - v.a;
	}
	if(ret.size() > 1 && bad(ret[0])) ret.pop_back();
	return ret;
}

vector<Point> minkowski_sub(const vector<Point> &a, const vector<Point> &b) {
	vector<Point> neg_b;
	neg_b.reserve(b.size());
	for(const auto &pt : b) neg_b.push_back(Point() - pt);
	return minkowski_add(a, neg_b);
}
