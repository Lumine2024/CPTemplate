#pragma once
#include "common.h"

template<class T, class F> struct Sparse {
	Sparse(const vector<T> &v, F f) : func(f) {
		int n = v.size();
		int k = bit_width<unsigned>(n);
		table.resize(n);
		for(int i = 0; i < n; ++i) {
			table[i][0] = v[i];
		}
		for(int j = 1; j < k; ++j) {
			int st = 1 << (j - 1);
			for(int i = 0; i + st < n; ++i) {
				table[i][j] = func(table[i][j - 1], table[i + st][j - 1]);
			}
		}
	}
	T query(int l, int r) const {
		int len = r - l;
		int j = bit_width<unsigned>(len) - 1;
		return func(table[l][j], table[r - 1 - (1 << j) + 1][j]);
	}

private:
	vector<array<T, 25>> table;
	F func;
};
template<class T, class F> Sparse(const vector<T> &v, F f) -> Sparse<T, F>;
