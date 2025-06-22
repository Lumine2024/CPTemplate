#pragma once
#include <bits/stdc++.h>
#include "Constants.hpp"
using namespace std;
using ll = long long;
using ull = unsigned long long;

template<class T> bool chkmin(T &x, const T &y) {
	if(x > y) {
		x = y;
		return true;
	}
	return false;
}

// 跑的dijkstra
ll remainder_mindist(ll k, vector<ll> dist) {
	ll modulo = 2 * min(dist[0], dist[3]);
	vector<vector<ll>> dp(4, vector<ll>(modulo, inf));
	vector<vector<bool>> visited(4, vector<bool>(modulo, false));
	dp[0][0] = 0;
	priority_queue<tuple<ll, ll, ll>, vector<tuple<ll, ll, ll>>, greater<>> pq;
	pq.emplace(0, 0, 0);
	auto get = [](ll a, ll b) -> ll {
		if(a == 3 && b == 0) {
			return 3;
		}
		if(b == 3 && a == 0) {
			return 3;
		}
		return min(a, b);
	};
	while(!pq.empty()) {
		auto [w, m, c] = pq.top();
		pq.pop();
		if(visited[c][m]) continue;
		visited[c][m] = true;
		ll d1 = (c + 1) % 4, d2 = (c + 3) % 4;
		ll w1 = dist[get(c, d1)], w2 = dist[get(c, d2)];
		if(chkmin(dp[d1][(w + w1) % modulo], w + w1)) {
			pq.emplace(w + w1, (w + w1) % modulo, d1);
		}
		if(chkmin(dp[d2][(w + w2) % modulo], w + w2)) {
			pq.emplace(w + w2, (w + w2) % modulo, d2);
		}
	}
	ll ans = inf;
	for(ll i = 0; i < modulo; ++i) {
		ll required = (k / modulo) * modulo + i;
		while(required < k) {
			required += modulo;
		}
		chkmin(ans, max(required, dp[0][i]));
	}
	return ans;
}