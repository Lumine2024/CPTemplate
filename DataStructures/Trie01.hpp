#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

struct Trie01 {
	Trie01() : nodes(1) {}
	void insert(ll val) {
		int now = 0;
		for(ll i = 62; i >= 0; --i) {
			ll flag = (val >> i) & 1;
			if(nodes[now].nxt[flag] == -1) {
				nodes[now].nxt[flag] = nodes.size();
				nodes.emplace_back();
			}
			now = nodes[now].nxt[flag];
		}
	}
	ll qmax_xor(ll val) const {
		int now = 0;
		ll ans = 0;
		for(ll i = 62; i >= 0; --i) {
			ll flag = (val >> i) & 1;
			if(nodes[now].nxt[1 ^ flag] != -1) {
				ans += (1ll << i);
				now = nodes[now].nxt[1 ^ flag];
			} else {
				now = nodes[now].nxt[flag];
			}
		}
		return ans;
	}
private:
	static constexpr int height = 63;
	struct Node {
		int nxt[2];
		Node() {
			nxt[0] = nxt[1] = -1;
		}
	};
	vector<Node> nodes;
};