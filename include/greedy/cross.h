#pragma once
#include "geo/int/basic.h"

bool cross_all(const vector<PointInt> &points) {
	bool okx = true, oky = true;
	ld xb = -1, yb = -1;
	for(auto [x, y] : points) {
		if(x != points[0].x) {
			if(yb == -1) {
				yb = y;
			} else if(yb != y) {
				okx = false;
			}
		}
		if(y != points[0].y) {
			if(xb == -1) {
				xb = x;
			} else if(xb != x) {
				oky = false;
			}
		}
	}
	return okx || oky;
}
