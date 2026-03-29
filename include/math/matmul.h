#pragma once
#include "common.h"

template<class T>
vector<vector<T>> matmul(const vector<vector<T>> &a,
						 const vector<vector<T>> &b) {
	int m = a.size(), n = a[0].size(), p = b[0].size();
	vector<vector<T>> ret(m, vector<T>(p, T(0)));
	for(int i = 0; i < m; ++i) {
		for(int j = 0; j < p; ++j) {
			for(int k = 0; k < n; ++k) {
				ret[i][j] = ret[i][j] + a[i][k] * b[k][j];
			}
		}
	}
	return ret;
}
template<class T> vector<vector<T>> matpow(vector<vector<T>> mat, ll n) {
	int M = mat.size();
	vector<vector<T>> ret(M, vector<T>(M, 0));
	for(int i = 0; i < M; ++i) {
		ret[i][i] = static_cast<T>(1);
	}
	for(; n != 0; n >>= 1, mat = matmul(mat, mat)) {
		if(n & 1ll) ret = matmul(ret, mat);
	}
	return ret;
}
