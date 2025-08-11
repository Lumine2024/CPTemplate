#pragma once
#include <bits/stdc++.h>
#include "Geometry/Basic.hpp"
using namespace std;
using ll = long long;
using ull = unsigned long long;

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