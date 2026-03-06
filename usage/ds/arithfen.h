#pragma once
#include "common.h"

template<class T>
concept FenwickInfo = requires(T a, T b) {
	T{};
	{ a + b } -> convertible_to<T>;
};
template<FenwickInfo T> struct Fenwick {
	explicit Fenwick(int n) : _nums(n + 1, 0), _n(n) {}
	T query(int x) const {
		T ans{};
		for(; x; x -= x & -x) ans = ans + _nums[x];
		return ans;
	}
	void update(int x, const T &v) {
		for(; x <= _n; x += x & -x) _nums[x] = _nums[x] + v;
	}

private:
	vector<T> _nums;
	int _n;
};
struct ArithmeticFenwick {
	explicit ArithmeticFenwick(int n) : f1(n + 2), f2(n + 2) {}
	// a*idx+b
	void update(int l, int r, ll a, ll b) {
		f1.update(l, b);
		f1.update(r + 1, -b - a * (r - l + 1));
		f2.update(l, a);
		f2.update(r + 1, -a);
	}
	ll query(ll idx) const {
		return f1.query(idx) + idx * f2.query(idx);
	}

private:
	Fenwick<ll> f1, f2;
};
