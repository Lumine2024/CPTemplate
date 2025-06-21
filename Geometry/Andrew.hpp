#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

struct Point {
	double x, y;
};
double cross(const Point &a, const Point &b, const Point &c) {
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}
vector<Point> andrew(vector<Point> &points) {
	sort(points.begin(), points.end(), [](const Point &a, const Point &b) {
		return a.x == b.x ? a.y < b.y : a.x < b.x;
	});
	int n = points.size();
	vector<Point> stk;
	for(int i = 1; i < n; ++i) {
		while(stk.size() > 1 &&
			cross(stk[stk.size() - 2], stk.back(), points[i]) <= 0) {
			stk.pop_back();
			}
		stk.push_back(points[i]);
	}
	int t = stk.size();
	for(int i = n - 1; i >= 0; --i) {
		while(stk.size() > t &&
			cross(stk[stk.size() - 2], stk.back(), points[i]) <= 0) {
			stk.pop_back();
			}
		stk.push_back(points[i]);
	}
	return stk;
}