#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

string manacher(const string &_s) {
	string s = "$";
	for(char ch : _s) {
		s += ch;
		s += '$';
	}
	int n = s.size();
	int max_right = 0;
	int center = 0;
	vector<int> dp(n, 0);
	auto expand = [&](int left, int right) {
		while(left >= 0 && right < n && s[left] == s[right]) {
			--left;
			++right;
		}
		return (right - left) / 2;
	};
	for(int i = 0; i < n; ++i) {
		int mirror = 2 * center - i;
		if(i >= max_right) {
			dp[i] = expand(i, i);
			max_right = i + dp[i];
			center = i;
		} else if(dp[mirror] == max_right - i) {
			dp[i] = expand(i - dp[mirror], i + dp[mirror]);
			max_right = i + dp[i];
			center = i;
		} else {
			dp[i] = min(dp[mirror], max_right - i);
		}
	}
	auto it = max_element(dp.begin(), dp.end());
	int id = it - dp.begin(), len = *it;
	string ret;
	for(int i = id - len + 1; i < id + len; ++i) {
		if(s[i] != '$') {
			ret += s[i];
		}
	}
	return ret;
}