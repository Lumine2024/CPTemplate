#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

namespace OneD {
// 01背包
ll knapsack_01(const vector<pair<int, ll>> &objects, int maxw) {
	int n = objects.size();
	vector<ll> dp(maxw + 1, 0);
	for(auto [w, v] : objects) {
		for(int j = maxw; j >= w; --j) {
			dp[j] = max(dp[j], dp[j - w] + v);
		}
	}
	return dp[maxw];
}
// 完全背包
ll knapsack_complete(const vector<pair<int, ll>> &objects, int maxw) {
	int n = objects.size();
	vector<ll> dp(maxw + 1, 0);
	for(auto [w, v] : objects) {
		for(int j = w; j <= maxw; ++j) {
			dp[j] = max(dp[j], dp[j - w] + v);
		}
	}
	return dp[maxw];
}
struct Object {
	int cost, cnt;
	ll w;
};
// 多重背包
ll multi_knapsack(const vector<Object> &objects, int maxw) {
	vector<ll> dp(maxw + 1, 0);
	for(auto [cost, cnt, w] : objects) {
		for(int _ = 0; _ < cnt; ++_) {
			for(int j = maxw; j >= cost; --j) {
				dp[j] = max(dp[j], dp[j - cost] + w);
			}
		}
	}
	return dp[maxw];
}
// 多重背包的二进制优化
ll multi_knapsack_binary(const vector<Object> &objects, int maxw) {
	vector<pair<int, ll>> objs;
	for(auto [cost, cnt, w] : objects) {
		int k = 1;
		while(cnt > 0) {
			int take = min(k, cnt);
			objs.emplace_back(cost * take, w * take);
			cnt -= take;
			k *= 2;
		}
	}
	return knapsack_01(objs, maxw);
}
// 缺少：多重背包的单调队列优化
}

namespace TwoD {
struct Object {
	int u, v;
	ll w;
};
// 二维01背包
ll knapsack_01(int U, int V, const vector<Object> &objects) {
	vector<vector<ll>> dp(U + 1, vector<ll>(V + 1, 0));
	for(auto [u, v, w] : objects) {
		for(int i = U; i - u >= 0; --i) {
			for(int j = V; j - v >= 0; --j) {
				dp[i][j] = max(dp[i][j], dp[i - u][j - v] + w);
			}
		}
	}
	return dp[U][V];
}

}