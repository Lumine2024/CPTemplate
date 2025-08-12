#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

struct SeqAM {
	explicit SeqAM(const string &s) : n(s.size()), nxt(s.size() + 2, [&] {
		array<int, 26> ret;
		ret.fill(s.size() + 1);
		return ret;
	}()) {
		for(int i = n - 1; i >= 0; --i) {
			nxt[i] = nxt[i + 1];
			nxt[i][s[i] - 'a'] = i + 1;
		}
	}
	bool match(const string &t) const {
		int now = 0;
		for(char c : t) {
			now = nxt[now][c - 'a'];
		}
		return now != (n + 1);
	}
private:
	int n;
	vector<array<int, 26>> nxt;
};