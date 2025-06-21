#pragma once
#include <bits/stdc++.h>
#include "DataStructures/FenwickTree.hpp"
using namespace std;
using ll = long long;
using ull = unsigned long long;

struct ArithmeticFenwick {
	ArithmeticFenwick(int n)
		: f1(n + 2), f2(n + 2) {}
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
	Fenwick f1, f2;
};