#pragma once
#include "common.h"

struct Item {
	ll w, v;
};

ll knapsack_01(const vector<Item> &s, int mw) {
	vector<ll> dp(mw + 1, 0);
	for(auto [w, v] : s) {
		for(int ww = mw; ww >= w; --ww) {
			chkmax(dp[ww], dp[ww - w] + v);
		}
	}
	return dp[mw];
}
ll knapsack_full(const vector<Item> &s, int mw) {
	vector<ll> dp(mw + 1, 0);
	for(auto [w, v] : s) {
		for(int ww = w; ww <= mw; ++ww) {
			chkmax(dp[ww], dp[ww - w] + v);
		}
	}
	return dp[mw];
}

struct MultiItem {
	ll w, v, cnt;
};

ll knapsack_multi(const vector<MultiItem> &s, int mw) {
	vector<Item> ss;
	for(auto [w, v, cnt] : s) {
		ll i = 1;
		while(i < cnt) {
			ss.push_back({w * i, v * i});
			cnt -= i;
			i *= 2;
		}
		ss.push_back({w * cnt, v * cnt});
	}
	return knapsack_01(ss, mw);
}