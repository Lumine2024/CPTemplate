#pragma once
#include "../constants.hpp"

vector<Point> andrew(vector<Point> points) {
	sort(points.begin(), points.end(), [](const Point &a, const Point &b) {
		return a.x < b.x || (a.x == b.x && a.y < b.y);
	});
	points.erase(unique(points.begin(), points.end()), points.end());
	int n = points.size();
	if(n <= 2) {
		return points;
	}
	vector<Point> stk;
	for(int i = 0; i < n; ++i) {
		while(stk.size() >= 2 && sign(cross(stk[stk.size() - 2], stk.back(), points[i])) <= 0) {
			stk.pop_back();
		}
		stk.push_back(points[i]);
	}
	int t = stk.size();
	for(int i = n - 2; i >= 0; --i) {
		while(stk.size() > t && sign(cross(stk[stk.size() - 2], stk.back(), points[i])) <= 0) {
			stk.pop_back();
		}
		stk.push_back(points[i]);
	}
	stk.pop_back();
	return stk;
}