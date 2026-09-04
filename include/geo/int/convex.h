#pragma once
#include "geo/int/basic.h"

array<int, 3> convex_max_triangle(const vector<PointInt> &cv) {
	int m = cv.size();
	if(m < 3) return {-1, -1, -1};
	auto get = [&](int i) { return cv[i % m]; };
	ll max_area = -1;
	array<int, 3> ret = {0, 1, 2};
	for(int i = 0; i < m; ++i) {
		int k = i + 2;
		for(int j = i + 1; j < i + m - 1; ++j) {
			while(k + 1 < i + m && cross(get(j) - get(i), get(k + 1) - get(i)) >
									   cross(get(j) - get(i), get(k) - get(i)))
				++k;
			ll area = cross(get(j) - get(i), get(k) - get(i));
			if(area > max_area) {
				max_area = area;
				ret = {i, j % m, k % m};
			}
		}
	}
	return ret;
}

pair<int, int> convex_farthest(const vector<PointInt> &cv) {
	int m = cv.size();
	if(m == 0) return {-1, -1};
	if(m == 1) return {0, 0};
	if(m == 2) return {0, 1};
	int j = 1;
	ll max_dist = 0;
	pair<int, int> ret = {0, 0};
	for(int i = 0; i < m; ++i) {
		int u = (i + 1) % m;
		while(cross(cv[i], cv[u], cv[(j + 1) % m]) > cross(cv[i], cv[u], cv[j]))
			j = (j + 1) % m;
		auto chmax = [&](int k) {
			ll now = (cv[k] - cv[j]).len2();
			if(now > max_dist) {
				max_dist = now;
				ret = {k, j};
			}
		};
		chmax(i);
		chmax(u);
	}
	return ret;
}

bool is_in_convex(const PointInt &pt, const vector<PointInt> &cv) {
	if(cv.empty()) return false;
	if(cv.size() == 1) return pt == cv[0];
	if(cv.size() == 2) return is_on(pt, LineSegInt(cv[0], cv[1]));
	auto check = [](const PointInt &a, const PointInt &b, const PointInt &c,
					const PointInt &p) {
		ll c1 = cross(b - a, p - a), c2 = cross(c - b, p - b),
		   c3 = cross(a - c, p - c);
		return (c1 >= 0 && c2 >= 0 && c3 >= 0) ||
			   (c1 <= 0 && c2 <= 0 && c3 <= 0);
	};
	int n = cv.size();
	PointInt pivot = cv[0];
	if(cross(cv[1] - pivot, pt - pivot) < 0 ||
	   cross(cv[n - 1] - pivot, pt - pivot) > 0)
		return false;
	int l = 1, r = n - 1;
	while(l + 1 < r) {
		int mid = (l + r) >> 1;
		if(cross(cv[mid] - pivot, pt - pivot) >= 0) l = mid;
		else r = mid;
	}
	int nxt = (l == n - 1) ? 1 : l + 1;
	return check(pivot, cv[l], cv[nxt], pt);
}

optional<pair<PointInt, PointInt>> convex_tangent(const PointInt &pt,
												  const vector<PointInt> &cv) {
	if(is_in_convex(pt, cv)) return nullopt;
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
		int idx = peak(2, n, dist2(cv[0], pt) < dist2(cv[1], pt));
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

pair<PointInt, PointInt> convex_tangent(const LineInt &ln,
										const vector<PointInt> &cv) {
	int n = cv.size();
	PointInt dir(-ln.v.y, ln.v.x);
	auto find = [&](bool f) {
		int l = 0, r = n - 1;
		while(r - l > 2) {
			int m1 = l + (r - l) / 3, m2 = r - (r - l) / 3;
			ll dot1 = dot(cv[m1], dir), dot2 = dot(cv[m2], dir);
			if(f ^ (dot1 < dot2)) r = m2;
			else l = m1;
		}
		int idx = l;
		ll ret = dot(cv[l], dir);
		for(int i = l; i <= r; ++i) {
			ll now = dot(cv[i], dir);
			if(f ^ (now < ret)) {
				idx = i;
				ret = now;
			}
		}
		return idx;
	};
	int i1 = find(true), i2 = find(false);
	return {cv[i1], cv[i2]};
}

vector<PointInt> minkowski_add(const vector<PointInt> &a,
							   const vector<PointInt> &b) {
	int n = a.size(), m = b.size();
	auto cmp = [](const LineSegInt &u, const LineSegInt &v) {
		return argcmp(u.b - u.a, v.b - v.a);
	};
	vector<LineSegInt> e1(n), e2(m), edge(n + m);
	for(int i = 0; i < n; ++i) e1[i] = {a[i], a[(i + 1) % n]};
	for(int i = 0; i < m; ++i) e2[i] = {b[i], b[(i + 1) % m]};
	rotate(e1.begin(), min_element(e1.begin(), e1.end(), cmp), e1.end());
	rotate(e2.begin(), min_element(e2.begin(), e2.end(), cmp), e2.end());
	merge(e1.begin(), e1.end(), e2.begin(), e2.end(), edge.begin(), cmp);
	vector<PointInt> ret;
	auto bad = [&](const PointInt &u) {
		PointInt b1 = ret.back(), b2 = *prev(ret.end(), 2);
		return to_left(b1 - b2, u - b1) == 0 && dot(b1 - b2, u - b1) >= 0;
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

vector<PointInt> minkowski_sub(const vector<PointInt> &a,
							   const vector<PointInt> &b) {
	vector<PointInt> neg_b;
	neg_b.reserve(b.size());
	for(const auto &pt : b) neg_b.push_back(PointInt() - pt);
	return minkowski_add(a, neg_b);
}
