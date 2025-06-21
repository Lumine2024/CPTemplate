#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

struct SegTree {
	const int n;
	SegTree(const vector<ll> &v)
		: n(v.size()), s(v.size() * 4), l(v.size() * 4) {
		_b(v, 0, 0, n);
	}
	SegTree(int sz) : n(sz), s(sz * 4, 0), l(sz * 4, 0) {}
	ll query(int l, int r) {
		if(l == r) return 0;
		return _q(l, r, 0, 0, n);
	}
	void update(int l, int r, ll d) {
		if(l == r) return;
		_u(l, r, d, 0, 0, n);
	}
private:
	vector<ll> s, l;
	void _b(const vector<ll> &v, int r, int rl, int rr) {
		if(rr - rl == 1) {
			s[r] = v[rl];
			return;
		}
		int m = (rl + rr) / 2;
		_b(v, r * 2 + 1, rl, m);
		_b(v, r * 2 + 2, m, rr);
		s[r] = s[r * 2 + 1] + s[r * 2 + 2];
	}
	void _pd(int r, int rl, int rr) {
		if(l[r] == 0) return;
		int m = (rl + rr) / 2;
		s[r * 2 + 1] += l[r] * (m - rl);
		l[r * 2 + 1] += l[r];
		s[r * 2 + 2] += l[r] * (rr - m);
		l[r * 2 + 2] += l[r];
		l[r] = 0;
	}
	ll _q(int ql, int qr, int r, int rl, int rr) {
		if(ql <= rl && qr >= rr) return s[r];
		_pd(r, rl, rr);
		int m = (rl + rr) / 2;
		ll ans = 0;
		if(ql < m) {
			ans += _q(ql, qr, r * 2 + 1, rl, m);
		}
		if(qr > m) {
			ans += _q(ql, qr, r * 2 + 2, m, rr);
		}
		return ans;
	}
	// 区间修改
	void _u(int ul, int ur, ll d, int r, int rl, int rr) {
		if(ul <= rl && ur >= rr) {
			s[r] += d * (rr - rl);
			l[r] += d;
			return;
		}
		_pd(r, rl, rr);
		int m = (rl + rr) / 2;
		if(ul < m) {
			_u(ul, ur, d, r * 2 + 1, rl, m);
		}
		if(ur > m) {
			_u(ul, ur, d, r * 2 + 2, m, rr);
		}
		s[r] = s[r * 2 + 1] + s[r * 2 + 2];
	}
	// 单点修改
	void __u(int x, ll v, int r, int rl, int rr) {
		if(rl == rr - 1) {
			s[r] += v;
			return;
		}
		int m = (rl + rr) / 2;
		if(x < m) {
			__u(x, v, r * 2 + 1, rl, m);
		} else {
			__u(x, v, r * 2 + 2, m, rr);
		}
		s[r] = s[r * 2 + 1] + s[r * 2 + 2];
	}
};