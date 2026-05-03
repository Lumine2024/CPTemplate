#pragma once
#include "common.h"

// persistent segment tree
struct PST {
	explicit PST(int n_) : n(n_) {
		l.reserve(2 * n * (int)log2(n));
		r.reserve(2 * n * (int)log2(n));
		cnt.reserve(2 * n * (int)log2(n));
		vers.reserve(n + 1);
		vers.push_back(_build(0, n - 1));
	}
	void update(int k) {
		vers.push_back(_update(k, vers.back(), 0, n - 1));
	}
	// 这里为解决静态区间第k小问题设计，传入k, l, r
	int query(int k, int ver1, int ver2) const {
		return _query(k, vers[ver1 - 1], vers[ver2], 0, n - 1);
	}

private:
	vector<int> l, r, cnt;
	vector<int> vers;
	int n;
	int _build(int l, int r) {
		int ret = size();
		this->l.push_back(-1);
		this->r.push_back(-1);
		cnt.push_back(0);
		if(l == r) {
			return ret;
		}
		int mid = (l + r) / 2;
		this->l[ret] = _build(l, mid);
		this->r[ret] = _build(mid + 1, r);
		return ret;
	}
	int _update(int k, int root, int l, int r) {
		int ret = size();
		this->l.push_back(this->l[root]);
		this->r.push_back(this->r[root]);
		cnt.push_back(cnt[root] + 1);
		if(l == r) return ret;
		int mid = (l + r) / 2;
		if(k <= mid) this->l[ret] = _update(k, this->l[root], l, mid);
		else this->r[ret] = _update(k, this->r[root], mid + 1, r);
		return ret;
	}
	int _query(int k, int root1, int root2, int l, int r) const {
		if(l == r) return l;
		int mid = (l + r) / 2;
		int cntl = cnt[this->l[root2]] - cnt[this->l[root1]];
		if(k <= cntl) return _query(k, this->l[root1], this->l[root2], l, mid);
		return _query(k - cntl, this->r[root1], this->r[root2], mid + 1, r);
	}
	int size() const {
		return cnt.size();
	}
};
