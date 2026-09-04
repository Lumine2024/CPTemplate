#pragma once
#include "geo/fp/basic.h"

struct Arc {
	int idx;
	ld alpha, beta;
};
vector<Arc> circle_inter(const vector<Circle> &circs) {
	int n = circs.size();
	vector<Arc> ret;
	for(int i = 0; i < n; ++i) {
		const Circle &ci = circs[i];
		vector<pair<ld, ld>> forbidden;
		forbidden.reserve(2 * n);
		bool empty = false;
		for(int j = 0; j < n; ++j) {
			if(j == i) continue;
			const Circle &cj = circs[j];
			if(cmp(ci.r, 0.0l) == 0) {
				if(!is_in(ci.c, cj)) empty = true;
				continue;
			}
			if(is_in(ci, cj)) continue;
			if(!is_inter(ci, cj)) {
				empty = true;
				break;
			}

			ld d = dist(ci.c, cj.c);
			ld cosa =
				clamp((ci.r * ci.r + d * d - cj.r * cj.r) / (2 * ci.r * d),
					  -1.0l, 1.0l);
			ld a = acos(cosa);
			if(cmp(a, 0.0l) == 0) {
				empty = true;
				break;
			}
			ld start = (cj.c - ci.c).arg() + a;
			if(start >= 2 * pi) start -= 2 * pi;
			ld len = 2 * pi - 2 * a;
			if(cmp(len, 0.0l) == 0) continue;
			ld end = start + len;
			if(end <= 2 * pi) {
				forbidden.emplace_back(start, end);
			} else {
				forbidden.emplace_back(start, 2 * pi);
				forbidden.emplace_back(0.0l, end - 2 * pi);
			}
		}
		if(empty) continue;
		if(forbidden.empty()) {
			ret.push_back({i, 0.0l, 2 * pi});
			continue;
		}
		sort(forbidden.begin(), forbidden.end());
		vector<pair<ld, ld>> merged;
		for(auto [l, r] : forbidden) {
			if(merged.empty() || cmp(l, merged.back().second) == 1) {
				merged.emplace_back(l, r);
			} else {
				merged.back().second = max(merged.back().second, r);
			}
		}
		vector<Arc> arcs;
		for(int k = 1; k < (int)merged.size(); ++k) {
			ld l = merged[k - 1].second, r = merged[k].first;
			if(cmp(l, r) == -1) arcs.push_back({i, l, r});
		}
		ld l = merged.back().second, r = merged.front().first + 2 * pi;
		if(cmp(l, r) == -1) {
			if(cmp(l, 2 * pi) == 0)
				arcs.push_back({i, 0.0l, merged.front().first});
			else arcs.push_back({i, l, r});
		}
		sort(arcs.begin(), arcs.end(),
			 [](const Arc &x, const Arc &y) { return x.alpha < y.alpha; });
		ret.insert(ret.end(), arcs.begin(), arcs.end());
	}
	return ret;
}
