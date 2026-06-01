#pragma once
#include "geo/basic.h"

vector<Point> andrew(vector<Point> ps) {
	sort(ps.begin(), ps.end(), [](const Point &a, const Point &b) {
		return a.x < b.x || (a.x == b.x && a.y < b.y);
	});
	ps.erase(unique(ps.begin(), ps.end()), ps.end());
	int n = ps.size();
	if(n <= 2) return ps;
	vector<Point> stk;
	for(int i = 0; i < n; ++i) {
		while(stk.size() >= 2 &&
			  sign(cross(stk[stk.size() - 2], stk.back(), ps[i])) <= 0)
			stk.pop_back();
		stk.push_back(ps[i]);
	}
	int t = stk.size();
	for(int i = n - 2; i >= 0; --i) {
		while((int)stk.size() > t &&
			  sign(cross(stk[stk.size() - 2], stk.back(), ps[i])) <= 0)
			stk.pop_back();
		stk.push_back(ps[i]);
	}
	stk.pop_back();
	return stk;
}
