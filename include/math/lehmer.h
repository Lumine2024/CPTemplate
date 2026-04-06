#pragma once
#include "math/preppow.h"
#include "ds/vst.h"
#include "ds/fenwick.h"

// 均为0-based排列
vector<int> lehmer(const vector<int> &a) {
	int n = a.size();
	vector<int> l(n);
	Fenwick<ll> bit(n);
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
	VST vst(n); // 使用权值线段树实现会快一点
	for(int i = 0; i < n; ++i) {
		vst.insert(i);
	}
	vector<int> ret(n);
	for(int i = 0; i < n; ++i) {
		ret[i] = vst.qvr(l[i] + 1);
		vst.erase(ret[i]);
	}
	return ret;
}
