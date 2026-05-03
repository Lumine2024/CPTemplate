#pragma once
#include "common.h"

struct SAM {
	SAM() : nxt(1), link(1, -1), len(1, 0), last(0) {
		nxt[0].fill(-1);
	}
	void insert(char ch) {
		const int id = ch - 'a';
		const int cur = size();
		nxt.emplace_back();
		nxt.back().fill(-1);
		link.push_back(-1);
		len.push_back(len[last] + 1);
		int p = last;
		while(p != -1 && nxt[p][id] == -1) {
			nxt[p][id] = cur;
			p = link[p];
		}
		if(p == -1) {
			link[cur] = 0;
		} else {
			int q = nxt[p][id];
			if(len[p] + 1 == len[q]) {
				link[cur] = q;
			} else {
				int clone = size();
				nxt.push_back(nxt[q]);
				link.push_back(link[q]);
				len.push_back(len[p] + 1);
				while(p != -1 && nxt[p][id] == q) {
					nxt[p][id] = clone;
					p = link[p];
				}
				link[q] = link[cur] = clone;
			}
		}
		last = cur;
		ends.push_back(cur);
	}
	ll solve() const {
		int n = size();
		vector<int> indeg(n, 0), topoorder;
		topoorder.reserve(n);
		for(int i = 0; i < n; ++i) {
			if(link[i] != -1) {
				indeg[link[i]]++;
			}
		}
		queue<int> q;
		for(int i = 0; i < n; ++i) {
			if(indeg[i] == 0) {
				q.push(i);
			}
		}
		while(!q.empty()) {
			int u = q.front();
			q.pop();
			topoorder.push_back(u);
			if(link[u] != -1) {
				indeg[link[u]]--;
				if(indeg[link[u]] == 0) {
					q.push(link[u]);
				}
			}
		}
		ll ans = 0;
		vector<ll> occur(n, 0);
		for(int e : ends) {
			occur[e] = 1;
		}
		for(int i : topoorder) {
			if(link[i] != -1) {
				occur[link[i]] += occur[i];
			}
			if(occur[i] != 1) {
				ans = max(ans, occur[i] * len[i]);
			}
		}
		return ans;
	}
	vector<array<int, 26>> nxt;
	vector<int> link, len;
	vector<int> ends;
	int last;
	int size() const {
		return nxt.size();
	}
};
