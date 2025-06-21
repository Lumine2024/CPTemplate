#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

void range_dp() {
	int n;
	cin >> n;
	vector<ll> nums(n);
	for(int i = 0; i < n; ++i) {
		cin >> nums[i];
	}
	vector<int> s(2 * n + 1);
	for(int i = 0; i < 2 * n; ++i) {
		s[i + 1] = s[i] + nums[i];
	}
	vector<vector<int>> dp(2 * n + 1, vector<int>(2 * n + 1));
	for(int len = 2; len <= n; ++len) {
		for(int i = 0; i <= 2 * n - len; ++i) {
			int j = i + len;
			int mx = 0;
			for(int k = i + 1; k < j; ++k) {
				mx = max(mx, dp[i][k] + dp[k][j]);
			}
			dp[i][j] = mx + s[j] - s[i];
		}
	}
	int ans = 0;
	for(int i = 0; i < n; ++i) {
		ans = max(ans, dp[i][i + n]);
	}
	cout << ans << '\n';
}