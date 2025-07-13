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
		if(l == r)
			return 0;
		return _query(l, r, 0, 0, n);
	}
	void update(int l, int r, ll dval) {
		if(l == r)
			return;
		_update(l, r, dval, 0, 0, n);
	}
private:
	mutable vector<ll> sum, lazy;
	void _build(const vector<ll> &v, int rt, int rl, int rr) {
		if(rr - rl == 1) {
			sum[rt] = v[rl];
			return;
		}
		int mid = (rl + rr) >> 1, lson = rt * 2 + 1, rson = rt * 2 + 2;
		_build(v, lson, rl, mid);
		_build(v, rson, mid, rr);
		sum[rt] = sum[lson] + sum[rson];
	}
	void _pushdown(int rt, int rl, int rr) const {
		if(lazy[rt] == 0)
			return;
		int mid = (rl + rr) >> 1, lson = rt * 2 + 1, rson = rt * 2 + 2;
		sum[lson] += lazy[rt] * (mid - rl);
		lazy[lson] += lazy[rt];
		sum[rson] += lazy[rt] * (rr - mid);
		lazy[rson] += lazy[rt];
		lazy[rt] = 0;
	}
	ll _query(int ql, int qr, int rt, int rl, int rr) const {
		if(ql <= rl && qr >= rr)
			return sum[rt];
		_pushdown(rt, rl, rr);
		int mid = (rl + rr) >> 1, lson = rt * 2 + 1, rson = rt * 2 + 2;
		ll ans = 0;
		if(ql < mid) {
			ans += _query(ql, qr, lson, rl, mid);
		}
		if(qr > mid) {
			ans += _query(ql, qr, rson, mid, rr);
		}
		return ans;
	}
	// 区间修改
	void _update(int ul, int ur, ll dv, int rt, int rl, int rr) {
		if(ul <= rl && ur >= rr) {
			sum[rt] += dv * (rr - rl);
			lazy[rt] += dv;
			return;
		}
		_pushdown(rt, rl, rr);
		int mid = (rl + rr) >> 1, lson = rt * 2 + 1, rson = rt * 2 + 2;
		if(ul < mid) {
			_update(ul, ur, dv, rt * 2 + 1, rl, mid);
		}
		if(ur > mid) {
			_update(ul, ur, dv, rt * 2 + 2, mid, rr);
		}
		sum[rt] = sum[rt * 2 + 1] + sum[rt * 2 + 2];
	}
	// 单点修改
	void __update(int x, ll v, int rt, int rl, int rr) {
		if(rl == rr - 1) {
			sum[rt] += v;
			return;
		}
		int mid = (rl + rr) >> 1, lson = rt * 2 + 1, rson = rt * 2 + 2;
		if(x < mid) {
			__update(x, v, lson, rl, mid);
		} else {
			__update(x, v, rt * 2 + 2, mid, rr);
		}
		sum[rt] = sum[lson] + sum[rson];
	}
};