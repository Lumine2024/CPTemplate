#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

struct SeqAM {
	SeqAM(const string &str)
	    : n(str.size()), nxt(str.size() + 1, [&] {
		      array<int, 26> ret;
		      ret.fill(str.size());
		      return ret;
	      }()) {
		for(int i = n - 1; i >= 0; --i) {
			nxt[i] = nxt[i + 1];
			nxt[i][str[i] - 'a'] = i;
		}
	}
	bool match(const string &str) const {
		int pos = 0;
		for(char ch : str) {
			pos = nxt[pos][ch - 'a'];
			if(pos == n)
				return false;
			pos++;
		}
		return true;
	}
private:
	int n;
	vector<array<int, 26>> nxt;
};