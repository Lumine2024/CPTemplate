#pragma once
#include "constants.hpp"
#include "ds/seg.hpp"

struct LisInfo {
	int val;
	LisInfo operator+(const LisInfo &r) const {
		return LisInfo{ max(val, r.val) };
	}
	void update(LisInfo &v) const {
		v.val += val;
	}
};

int lis_seg(const vector<int> &nums) {
	auto discrete = nums;
	sort(discrete.begin(), discrete.end());
	discrete.erase(unique(discrete.begin(), discrete.end()), discrete.end());
	auto getid = [&](int x) -> int {
		return lower_bound(discrete.begin(), discrete.end(), x) - discrete.begin();
	};
	SegTree<LisInfo> seg(discrete.size());
	for(int i = 0; i < nums.size(); i++) {
		int x = getid(nums[i]);
		int v = seg.query(0, x).val + 1;
		seg.update(x, LisInfo{ v });
	}
	return seg.query(0, discrete.size()).val;
}