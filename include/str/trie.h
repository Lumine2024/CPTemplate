#pragma once
#include "common.h"

template<int N, class F>
struct Trie {
	Trie() : nxt(1), end(1), cnt(1) {
		nxt[0].fill(-1);
	}
	void insert(const string &str) {
		int rt = 0;
		for(int i = 0; i < str.size(); ++i) {
			int id = mapper(str[i]);
			if(nxt[rt][id] == -1) {
				nxt[rt][id] = size();
				nxt.emplace_back();
				nxt.back().fill(-1);
				end.push_back(false);
				cnt.push_back(0);
			}
			cnt[rt]++;
			rt = nxt[rt][id];
		}
		cnt[rt]++;
		end[rt] = true;
	}
	bool find(const string &str) const {
		int rt = 0;
		for(int i = 0; i < str.size(); ++i) {
			int id = mapper(str[i]);
			if(nxt[rt][id] == -1) {
				return false;
			}
			rt = nxt[rt][id];
		}
		return end[rt];
	}
	int prefix_count(const string &str) const {
		int rt = 0;
		for(int i = 0; i < str.size(); ++i) {
			int id = mapper(str[i]);
			if(nxt[rt][id] == -1) {
				return 0;
			}
			rt = nxt[rt][id];
		}
		return cnt[rt];
	}

private:
	vector<array<int, N>> nxt;
	vector<bool> end;
	vector<int> cnt;
	F mapper;
	int size() const {
		return nxt.size();
	}
};
