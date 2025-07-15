#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

struct SAM {
	SAM() : nodes(1, Node(-1, 0)), last(0) {}
	void insert(char ch) {
		const int id = ch - 'a';
		const int cur = nodes.size();
		nodes.emplace_back(-1, nodes[last].len + 1);
		int p = last;
		while(p != -1 && nodes[p].nxt[id] == -1) {
			nodes[p].nxt[id] = cur;
			p = nodes[p].link;
		}
		if(p == -1) {
			nodes[cur].link = 0;
		} else {
			int q = nodes[p].nxt[id];
			if(nodes[p].len + 1 == nodes[q].len) {
				nodes[cur].link = q;
			} else {
				int clone = nodes.size();
				nodes.emplace_back(nodes[q].link, nodes[p].len + 1);
				nodes[clone].nxt = nodes[q].nxt;
				while(p != -1 && nodes[p].nxt[id] == q) {
					nodes[p].nxt[id] = clone;
					p = nodes[p].link;
				}
				nodes[q].link = nodes[cur].link = clone;
			}
		}
		last = cur;
		ends.push_back(cur);
	}
	ll solve() const {
		int n = nodes.size();
		vector<int> indeg(n, 0), topoorder;
		topoorder.reserve(n);
		for(int i = 0; i < n; ++i) {
			if(nodes[i].link != -1) {
				indeg[nodes[i].link]++;
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
			if(nodes[u].link != -1) {
				indeg[nodes[u].link]--;
				if(indeg[nodes[u].link] == 0) {
					q.push(nodes[u].link);
				}
			}
		}
		ll ans = 0;
		vector<ll> occur(n, 0);
		for(int e : ends) {
			occur[e] = 1;
		}
		for(int i : topoorder) {
			if(nodes[i].link != -1) {
				occur[nodes[i].link] += occur[i];
			}
			if(occur[i] != 1) {
				ans = max(ans, occur[i] * nodes[i].len);
			}
		}
		return ans;
	}
private:
	struct Node {
		array<int, 26> nxt;
		int link;
		int len;
		Node(int lk, int ln) : link(lk), len(ln) {
			nxt.fill(-1);
		}
	};
	vector<Node> nodes;
	vector<int> ends;
	int last;
};