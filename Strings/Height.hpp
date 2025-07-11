#pragma once
#include "SuffixArray.hpp"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

vector<int> height(const string &str) {
	int n = str.size();
	vector<int> sa = suffix_array(str), rk(n), h(n);
	for(int i = 0; i < n; ++i) {
		rk[sa[i]] = i;
	}
	for(int i = 0, k = 0; i < n; ++i) {
		if(rk[i] == 0) {
			continue;
		}
		if(k > 0) {
			--k;
		}
		while(str[i + k] == str[sa[rk[i] - 1] + k]) {
			++k;
		}
		h[rk[i]] = k;
	}
	return h;
}
