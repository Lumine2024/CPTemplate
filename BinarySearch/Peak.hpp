#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

int peak(const vector<int> &nums) {
	int n = nums.size();
	int l = 0, r = n - 1;
	int ll = (r - l) / 3, rr = (r - l) * 2 / 3;
	while(l < r) {
		if(nums[ll] < nums[rr]) {
			l = ll + 1;
		} else {
			r = rr;
		}
		ll = l + (r - l) / 3;
		rr = l + (r - l) * 2 / 3;
	}
	return l;
}