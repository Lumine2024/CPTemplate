#pragma once
#include "common.h"

struct ACAM {
	ACAM() : nxt(1), fail(1, 0) {
		nxt[0].fill(-1);
	}
	void insert(const string &str) {
		int rt = 0;
		for(int i = 0; i < (int)str.size(); ++i) {
			int id = str[i] - '0';
			if(nxt[rt][id] == -1) {
				nxt[rt][id] = size();
				nxt.emplace_back();
				nxt.back().fill(-1);
				fail.push_back(0);
			}
			rt = nxt[rt][id];
		}
	}
	void build() {
		queue<int> q;
		for(int i = 0; i < 2; ++i) {
			int v = nxt[0][i];
			if(v != -1) {
				fail[v] = 0;
				q.push(v);
			} else {
				nxt[0][i] = 0;
			}
		}
		while(!q.empty()) {
			int rt = q.front();
			q.pop();
			for(int i = 0; i < 2; ++i) {
				int v = nxt[rt][i];
				if(v != -1) {
					fail[v] = nxt[fail[rt]][i];
					q.push(v);
				} else {
					nxt[rt][i] = nxt[fail[rt]][i];
				}
			}
		}
	}
	vector<array<int, 2>> nxt;
	vector<int> fail;
	int size() const {
		return nxt.size();
	}
};
