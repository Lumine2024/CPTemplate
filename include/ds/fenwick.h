#pragma once
#include "common.h"

template<class T>
concept FenwickInfo = requires(T a, T b) {
	T{};
	{ a + b } -> convertible_to<T>;
};
template<FenwickInfo T>
struct Fenwick {
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
template<class T>
concept RangeFenwickInfo = requires(T a, T b, int c) {
	{ a - b } -> convertible_to<T>;
	{ a * c } -> convertible_to<T>;
	{ -a } -> convertible_to<T>;
} && FenwickInfo<T>;
template<RangeFenwickInfo T>
struct RangeFenwick {
	explicit RangeFenwick(int n) : _f1(n), _f2(n), _n(n) {}
	void update(int l, int r, const T &v) {
		_update(l, v);
		_update(r, -v);
	}
	T query(int x) const {
		return x * _f1.query(x) - _f2.query(x);
	}

private:
	Fenwick<T> _f1, _f2;
	int _n;
	void _update(int x, const T &v) {
		_f1.update(x, v);
		_f2.update(x, v * (x - 1));
	}
};
