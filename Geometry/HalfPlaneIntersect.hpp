#pragma once
#include <bits/stdc++.h>
#include "Geometry/Basic.hpp"
using namespace std;
using ll = long long;
using ull = unsigned long long;

vector<Line> half_inter(vector<Line> lines) {
	lines.push_back({{-inf, 0.0l}, {0.0l, -1.0l}});
	lines.push_back({{inf, 0.0l}, {0.0l, 1.0l}});
	lines.push_back({{0.0l, inf}, {-1.0l, 0.0l}});
	lines.push_back({{0.0l, -inf}, {1.0l, 0.0l}});
	sort(lines.begin(), lines.end(), [](const Line &a, const Line &b) {
		int c = cmp(a.v.arg(), b.v.arg());
		if(c != 0)
			return c == -1;
		return sign(cross(a.v, b.p - a.p)) < 0;
	});
	deque<Line> dq;
	auto bad = [](const Line &l, const Line &b, const Line &c) {
		auto p = inter(b, c);
		return to_left(l, p) < 0;
	};
	for(auto &l : lines) {
		if(!dq.empty() && cmp(l.v.arg(), dq.back().v.arg()) == 0) {
			if(to_left(l, dq.back().p + dq.back().v) < 0)
				dq.back() = l;
			continue;
		}
		while(dq.size() > 1 && bad(l, dq.back(), dq[dq.size() - 2]))
			dq.pop_back();
		while(dq.size() > 1 && bad(l, dq[0], dq[1]))
			dq.pop_front();
		dq.push_back(l);
	}
	while(dq.size() > 1 && bad(dq[0], dq.back(), dq[dq.size() - 2]))
		dq.pop_back();
	while(dq.size() > 1 && bad(dq.back(), dq[0], dq[1]))
		dq.pop_front();
	return vector<Line>(dq.begin(), dq.end());
}