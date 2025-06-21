#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

constexpr ll modulo = 10'0000'0007;
ll count_dp(string s) {
	int n = s.size();
	vector<vector<ll>> dp(n, vector<ll>(n, 0));
	dp[0][0] = 1;
	vector<vector<ll>> sum(n, vector<ll>(n + 1, 0));
	sum[0][1] = 1;
	for(int i = 1; i < n; ++i) {
		for(int j = 0; j <= i; ++j) {
			if(s[i - 1] == '<') {
				dp[i][j] = sum[i - 1][j];
			} else {
				dp[i][j] = (sum[i - 1][i] - sum[i - 1][j] + modulo) % modulo;
			}
		}
		sum[i][0] = 0;
		for(int j = 1; j <= i + 1; ++j) {
			sum[i][j] = (sum[i][j - 1] + dp[i][j - 1]) % modulo;
		}
	}
	ll ans = 0;
	for(int j = 0; j < n; ++j) {
		ans = (ans + dp[n - 1][j]) % modulo;
	}
}