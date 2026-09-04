#pragma once
#include "common.h"

template<class T>
concept FenwickInfo = requires(T a, T b) {
	T{};
	{ a + b } -> convertible_to<T>;
};
template<FenwickInfo T>
struct Fenwick {
	explicit Fenwick(int _n) : nums(_n + 1, 0), n(_n) {}
	T query(int x) const {
		T ans{};
		for(; x; x -= x & -x) ans = ans + nums[x];
		return ans;
	}
	void update(int x, const T &v) {
		for(; x <= n; x += x & -x) nums[x] = nums[x] + v;
	}

private:
	vector<T> nums;
	int n;
};
template<class T>
concept RangeFenwickInfo = requires(T a, T b, int c) {
	{ a - b } -> convertible_to<T>;
	{ a * c } -> convertible_to<T>;
	{ -a } -> convertible_to<T>;
} && FenwickInfo<T>;
template<RangeFenwickInfo T>
struct RangeFenwick {
	explicit RangeFenwick(int _n) : f1(_n), f2(_n), n(_n) {}
	void update(int l, int r, const T &v) {
		_update(l, v);
		_update(r, -v);
	}
	T query(int x) const {
		return x * f1.query(x) - f2.query(x);
	}

private:
	Fenwick<T> f1, f2;
	int n;
	void _update(int x, const T &v) {
		f1.update(x, v);
		f2.update(x, v * (x - 1));
	}
};
