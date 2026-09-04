#pragma once
#include "geo/int/basic.h"

vector<PointInt> andrew(vector<PointInt> ps) {
	sort(ps.begin(), ps.end(), [](const PointInt &a, const PointInt &b) {
		return a.x < b.x || (a.x == b.x && a.y < b.y);
	});
	ps.erase(unique(ps.begin(), ps.end()), ps.end());
	int n = ps.size();
	if(n <= 2) return ps;
	vector<PointInt> stk;
	for(int i = 0; i < n; ++i) {
		while(stk.size() >= 2 &&
			  cross(stk[stk.size() - 2], stk.back(), ps[i]) <= 0)
			stk.pop_back();
		stk.push_back(ps[i]);
	}
	int t = stk.size();
	for(int i = n - 2; i >= 0; --i) {
		while((int)stk.size() > t &&
			  cross(stk[stk.size() - 2], stk.back(), ps[i]) <= 0)
			stk.pop_back();
		stk.push_back(ps[i]);
	}
	stk.pop_back();
	return stk;
}
