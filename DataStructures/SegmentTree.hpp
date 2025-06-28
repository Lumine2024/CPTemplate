#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

struct SegTree {
	int n;
	SegTree(const vector<ll> &v)
		: n(v.size()), sum(v.size() * 4), lazy(v.size() * 4, 0) {
		_build(v, 0, 0, n);
	}
	SegTree(int sz) : n(sz), sum(sz * 4, 0), lazy(sz * 4, 0) {}
	SegTree() : n(0) {}
	void assign(int sz) {
		n = sz;
		sum.assign(n * 4, 0);
		lazy.assign(n * 4, 0);
	}
	void assign(const vector<ll> &v) {
		n = v.size();
		sum.assign(v.size() * 4, 0);
		lazy.assign(v.size() * 4, 0);
		_build(v, 0, 0, n);
	}
	ll query(int l, int r) const {
		if(l == r) return 0;
		return _query(l, r, 0, 0, n);
	}
	void update(int l, int r, ll dval) {
		if(l == r) return;
		_update(l, r, dval, 0, 0, n);
	}
private:
	void _build(const vector<ll> &v, int r, int rl, int rr) {
		if(rr - rl == 1) {
			sum[r] = v[rl];
			return;
		}
		int m = (rl + rr) / 2;
		_build(v, r * 2 + 1, rl, m);
		_build(v, r * 2 + 2, m, rr);
		sum[r] = sum[r * 2 + 1] + sum[r * 2 + 2];
	}
	void _pushdown(int root, int rl, int rr) const {
		if(lazy[root] == 0) return;
		int m = (rl + rr) / 2;
		sum[root * 2 + 1] += lazy[root] * (m - rl);
		lazy[root * 2 + 1] += lazy[root];
		sum[root * 2 + 2] += lazy[root] * (rr - m);
		lazy[root * 2 + 2] += lazy[root];
		lazy[root] = 0;
	}
	ll _query(int ql, int qr, int root, int rl, int rr) const {
		if(ql <= rl && qr >= rr) return sum[root];
		_pushdown(root, rl, rr);
		int mid = (rl + rr) / 2;
		ll ans = 0;
		if(ql < mid) {
			ans += _query(ql, qr, root * 2 + 1, rl, mid);
		}
		if(qr > mid) {
			ans += _query(ql, qr, root * 2 + 2, mid, rr);
		}
		return ans;
	}
	// 区间修改
	void _update(int ul, int ur, ll dv, int root, int rl, int rr) {
		if(ul <= rl && ur >= rr) {
			sum[root] += dv * (rr - rl);
			lazy[root] += dv;
			return;
		}
		_pushdown(root, rl, rr);
		int mid = (rl + rr) / 2;
		if(ul < mid) {
			_update(ul, ur, dv, root * 2 + 1, rl, mid);
		}
		if(ur > mid) {
			_update(ul, ur, dv, root * 2 + 2, mid, rr);
		}
		sum[root] = sum[root * 2 + 1] + sum[root * 2 + 2];
	}
	// 单点修改
	void __update(int x, ll v, int root, int rl, int rr) {
		if(rl == rr - 1) {
			sum[root] += v;
			return;
		}
		int mid = (rl + rr) / 2;
		if(x < mid) {
			__update(x, v, root * 2 + 1, rl, mid);
		} else {
			__update(x, v, root * 2 + 2, mid, rr);
		}
		sum[root] = sum[root * 2 + 1] + sum[root * 2 + 2];
	}
	mutable vector<ll> sum, lazy;
};