#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

template<class T>
vector<vector<T>> matmul(const vector<vector<T>> &lhs, const vector<vector<T>> &rhs) {
	int M = lhs.size(), N = lhs[0].size(), P = rhs[0].size();
	vector<vector<T>> ret(M, vector<T>(P, 0));
	for(int i = 0; i < M; ++i) {
		for(int j = 0; j < P; ++j) {
			for(int k = 0; k < N; ++k) {
				ret[i][j] = ret[i][j] + lhs[i][k] * rhs[k][j];
			}
		}
	}
	return ret;
}
template<class T>
vector<vector<T>> matpow(vector<vector<T>> mat, ll N) {
	int M = mat.size();
	vector<vector<T>> ret(M, vector<T>(M, 0));
	for(int i = 0; i < M; ++i) {
		ret[i][i] = static_cast<T>(1);
	}
	while(N) {
		if(N & 1ll) {
			ret = matmul(ret, mat);
		}
		mat = matmul(mat, mat);
		N >>= 1;
	}
	return ret;
}