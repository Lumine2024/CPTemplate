#pragma once
#include "constants.hpp"
#include "geo/basic.hpp"
#include "geo/andrew.hpp"

ld farthest_dist(const vector<Point> &pts) {
    int n = pts.size();
    auto hull = andrew(pts);
	int m = hull.size();
	int j = 1;
	ld ans = 0;
	for(int i = 0; i < m; ++i) {
		int u = (i + 1) % m;
		while(cross(hull[i], hull[u], hull[(j + 1) % m]) > cross(hull[i], hull[u], hull[j])) {
			j = (j + 1) % m;
		}
		ans = max({ ans, (hull[i] - hull[j]).len2(), (hull[u] - hull[j]).len2() });
	}
    return ans;
}