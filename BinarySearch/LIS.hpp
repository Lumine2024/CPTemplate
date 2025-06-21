#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

int lis(const vector<int> &nums) {
	vector<int> lis;
	for(int i : nums) {
		auto it = lower_bound(lis.begin(), lis.end(), i);
		if(it == lis.end()) {
			lis.push_back(i);
		} else {
			*it = i;
		}
	}
	return lis.size();
}