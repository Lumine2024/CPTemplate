#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

// value segment tree
struct VST {
	VST(int maxn) : sum((maxn + 1) * 4), n(maxn + 1) {}
	VST() : n(0) {}
	void assign(int maxn) {
		sum.assign((maxn + 1) * 4, 0);
		n = maxn + 1;
	}
	void insert(int x) {
		_update(x, 1, 0, 0, n);
	}
	void erase(int x) {
		_update(x, -1, 0, 0, n);
	}
	int qpre(int x) const {
		int rk = qrv(x);
		return qvr(rk - 1);
	}
	int qsuc(int x) const {
		int rk = qrv(x + 1);
		return qvr(rk);
	}
	int qrv(int x) const {
		return _query(0, x, 0, 0, n);
	}
	int qvr(int k) const {
		return _qvr(k, 0, 0, n);
	}
	int size() const {
		return sum[0];
	}
	int qcnt(int x) const {
		return _query(x, x + 1, 0, 0, n);
	}
	int qrange_cnt(int l, int r) const {
		return _query(l, r, 0, 0, n);
	}
private:
	vector<int> sum;
	int n;
	void _update(int x, int dv, int rt, int rl, int rr) {
		if(rr - rl == 1) {
			sum[rt] += dv;
			return;
		}
		int mid = (rl + rr) >> 1, lson = rt * 2 + 1, rson = rt * 2 + 2;
		if(x < mid) {
			_update(x, dv, lson, rl, mid);
		} else {
			_update(x, dv, rson, mid, rr);
		}
		sum[rt] = sum[lson] + sum[rson];
	}
	ll _query(int ql, int qr, int rt, int rl, int rr) const {
		if(ql <= rl && qr >= rr)
			return sum[rt];
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
	int _qvr(int k, int rt, int rl, int rr) const {
		if(rr - rl == 1)
			return rl;
		int mid = (rl + rr) >> 1, lson = rt * 2 + 1, rson = rt * 2 + 2;
		if(k < sum[lson]) {
			return _qvr(k, lson, rl, mid);
		} else {
			return _qvr(k - sum[lson], rson, mid, rr);
		}
	}
};