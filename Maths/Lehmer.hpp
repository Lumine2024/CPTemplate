#pragma once
#include <bits/stdc++.h>
#include "DataStructures/FenwickTree.hpp"
#include "DataStructures/Treap.hpp"
using namespace std;
using ll = long long;
using ull = unsigned long long;

// 均为0-based排列
vector<int> lehmer(const vector<int> &a) {
	int n = a.size();
	vector<int> l(n);
	Fenwick bit(n);
	for(int i = 1; i <= n; ++i) {
		bit.update(i, 1);
	}
	for(int i = 0; i < n; ++i) {
		int x = a[i] + 1;
		l[i] = bit.query(n) - bit.query(x);
		bit.update(x, -1);
	}
	return l;
}
vector<int> rev_lehmer(const vector<int> &l) {
	int n = l.size();
	Treap treap;
	for(int i = 0; i < n; ++i) {
		treap.insert(i);
	}
	vector<int> ret(n);
	for(int i = 0; i < n; ++i) {
		ret[i] = treap.qvr(l[i] + 1);
		treap.erase(ret[i]);
	}
	return ret;
}