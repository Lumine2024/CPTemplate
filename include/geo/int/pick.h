#pragma once
#include "geo/int/basic.h"

ll polygon_twice_area(const vector<PointInt> &polygon) {
	ll ret = 0;
	for(int i = 0; i < (int)polygon.size(); ++i)
		ret += cross(polygon[i], polygon[(i + 1) % polygon.size()]);
	return abs(ret);
}
ll points_inside(const vector<PointInt> &polygon) {
	ll twos = polygon_twice_area(polygon);
	ll border = 0;
	for(int i = 0; i < (int)polygon.size(); ++i) {
		int j = (i + 1) % polygon.size();
		PointInt v = polygon[j] - polygon[i];
		border += gcd(abs(v.x), abs(v.y));
	}
	return (twos - border + 2) / 2;
}
