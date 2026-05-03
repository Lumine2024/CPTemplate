#pragma once
#include "common.h"

struct Trie01 {
	Trie01() : nxt(1) {
		nxt[0][0] = nxt[0][1] = -1;
	}
	void insert(ll val) {
		int now = 0;
		for(ll i = 62; i >= 0; --i) {
			ll flag = (val >> i) & 1;
			if(nxt[now][flag] == -1) {
				nxt[now][flag] = size();
				nxt.push_back({-1, -1});
			}
			now = nxt[now][flag];
		}
	}
	ll qmax_xor(ll val) const {
		int now = 0;
		ll ans = 0;
		for(ll i = 62; i >= 0; --i) {
			ll flag = (val >> i) & 1;
			if(nxt[now][1 ^ flag] != -1) {
				ans += (1ll << i);
				now = nxt[now][1 ^ flag];
			} else {
				now = nxt[now][flag];
			}
		}
		return ans;
	}

private:
	static constexpr int height = 63;
	vector<array<int, 2>> nxt;
	int size() const {
		return nxt.size();
	}
};
