#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

// 单点
struct Fenwick {
	const int n;
	Fenwick(int n)
		: n(n), nums(n + 1) {}
	ll query(int x) const {
		ll ans = 0;
		for(; x; x -= lbit(x)) {
			ans += nums[x];
		}
		return ans;
	}
	void update(int x, ll v) {
		for(; x <= n; x += lbit(x)) {
			nums[x] += v;
		}
	}
private:
	vector<ll> nums;
	static int lbit(int x) {
		return x & -x;
	}
};
// 区间
struct RangeFenwick {
	const int n;
	RangeFenwick(int n)
		: n(n), f1(n), f2(n) {}
	void update(int l, int r, ll v) {
		_update(l, v);
		_update(r + 1, -v);
	}
	ll query(int l, int r) const {
		return _query(r) - _query(l - 1);
	}
private:
	Fenwick f1, f2;
	void _update(int x, ll v) {
		f1.update(x, v);
		f2.update(x, v * (x - 1));
	}
	ll _query(int x) const {
		return f1.query(x) * x - f2.query(x);
	}
};