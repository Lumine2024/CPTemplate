#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

struct SegTree {
	SegTree(ll n) {}
	ll query(int l, int r) const {
		return 0;
	}
	void update(int x, ll v) {

	}
};

// SegTree区间最大值、单点加法线段树
int lis(const vector<int> &nums) {
	auto discrete = nums;
	sort(discrete.begin(), discrete.end());
	discrete.erase(unique(discrete.begin(), discrete.end()), discrete.end());
	unordered_map<int, int> mp;
	for(int i = 0; i < discrete.size(); i++) {
		mp[discrete[i]] = i;
	}
	SegTree seg(discrete.size());
	for(int i = 0; i < nums.size(); i++) {
		int x = mp[nums[i]];
		int v = seg.query(0, x) + 1;
		seg.update(x, v);
	}
	return seg.query(0, discrete.size());
}