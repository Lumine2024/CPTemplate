#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

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
	unordered_map<int, int> mp;
	for(int i = 0; i < discrete.size(); i++) {
		mp[discrete[i]] = i;
	}
	SegTree<LisInfo> seg(discrete.size());
	for(int i = 0; i < nums.size(); i++) {
		int x = mp[nums[i]];
		int v = seg.query(0, x).val + 1;
		seg.update(x, LisInfo{ v });
	}
	return seg.query(0, discrete.size()).val;
}