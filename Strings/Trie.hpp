#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

struct Trie {
	Trie() : nodes(1) {}
	void insert(const string &str) {
		int rt = 0;
		for(int i = 0; i < str.size(); ++i) {
			if((nodes[rt].nxt[getnum(str[i])]) == -1) {
				nodes[rt].nxt[getnum(str[i])] = nodes.size();
				nodes.emplace_back();
			}
			nodes[rt].cnt++;
			rt = nodes[rt].nxt[getnum(str[i])];
		}
		nodes[rt].cnt++;
		nodes[rt].end = true;
	}
	bool find(const string &str) const {
		int rt = 0;
		for(int i = 0; i < str.size(); ++i) {
			if((nodes[rt].nxt[getnum(str[i])]) == -1) {
				return false;
			}
			rt = nodes[rt].nxt[getnum(str[i])];
		}
		return nodes[rt].end;
	}
	int find_prefix(const string &str) const {
		int rt = 0;
		for(int i = 0; i < str.size(); ++i) {
			if((nodes[rt].nxt[getnum(str[i])]) == -1) {
				return 0;
			}
			rt = nodes[rt].nxt[getnum(str[i])];
		}
		return nodes[rt].cnt;
	}
private:
	struct Node {
		array<int, 65> nxt;
		bool end;
		int cnt;
		Node() : end(false), cnt(0) {
			nxt.fill(-1);
		}
	};
	vector<Node> nodes;
	static int getnum(char x) {
		if(x >= 'A' && x <= 'Z') {
			return x - 'A';
		} else if(x >= 'a' && x <= 'z') {
			return x - 'a' + 26;
		} else {
			return x - '0' + 52;
		}
	}
};