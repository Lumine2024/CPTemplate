#pragma once
#include "common.h"

struct PAM {
	PAM() : s("#"), last(1) {
		nxt.emplace_back();
		nxt.back().fill(-1);
		len.push_back(-1);
		fail.push_back(0);
		cnt.push_back(0);
		nxt.emplace_back();
		nxt.back().fill(-1);
		len.push_back(0);
		fail.push_back(0);
		cnt.push_back(0);
	}
	int insert(char ch) {
		s += ch;
		int pos = s.size() - 1;
		int p = last, id = ch - 'a';
		while(s[pos - len[p] - 1] != ch) p = fail[p];
		if(nxt[p][id] == -1) {
			int cur = size();
			nxt[p][id] = cur;
			nxt.emplace_back();
			nxt.back().fill(-1);
			len.push_back(len[p] + 2);
			fail.push_back(0);
			cnt.push_back(0);
			if(len[cur] == 1) {
				fail[cur] = 1;
			} else {
				int f = fail[p];
				while(s[pos - len[f] - 1] != ch) f = fail[f];
				fail[cur] = nxt[f][id];
			}
			cnt[cur] = len[cur] == 1 ? 1 : cnt[fail[cur]] + 1;
		}
		last = nxt[p][id];
		return cnt[last];
	}
	vector<int> len, fail, cnt;
	vector<array<int, 26>> nxt;
	string s;
	int last;
	int size() const {
		return len.size();
	}
};
