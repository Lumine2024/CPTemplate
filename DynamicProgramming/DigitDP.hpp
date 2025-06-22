#pragma once
#include <bits/stdc++.h>
#include "Constants.hpp"
using namespace std;
using ll = long long;
using ull = unsigned long long;

ll digit_dp(string k, int d) {
	vector<vector<ll>> memo(k.size(), vector<ll>(d, -1));
	auto dfs = [&](auto &&dfs, int idx, ll psum, bool isnum, bool islimit) -> ll {
		if(idx == k.size()) {
			return (ll)(isnum && (psum == 0));
		}
		if(memo[idx][psum] != -1 && isnum && !islimit) {
			return memo[idx][psum];
		}
		ll ans = 0;
		if(!isnum) {
			ans = (ans + dfs(dfs, idx + 1, 0, false, false)) % modulo;
		}
		int llim = isnum ? 0 : 1, hlim = islimit ? (k[idx] - '0') : 9;
		for(int i = llim; i <= hlim; ++i) {
			ans = (ans + dfs(dfs, idx + 1, ((psum + i) % d), true, (islimit && (i == hlim)))) % modulo;
		}
		if(isnum && !islimit) {
			memo[idx][psum] = ans;
		}
		return ans;
	};
	return dfs(dfs, 0, 0, false, true);
}