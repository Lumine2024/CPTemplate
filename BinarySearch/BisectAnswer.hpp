#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

int binary(auto &&check) {
	int lo = 0, hi = 0x3f3f3f3f;
	int ans = -1;
	while(lo < hi) {
		int mid = (lo + hi) >> 1;
		if(check(mid)) {
			ans = mid;
			hi = mid - 1;
		} else {
			lo = mid + 1;
		}
	}
	return ans;
}