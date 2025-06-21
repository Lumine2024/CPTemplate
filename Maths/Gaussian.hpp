#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

vector<double> gauss(const vector<vector<double>> &A, const vector<double> &B) {
	int n = A.size();
	if(n == 0 || A[0].size() != n) return {};
	vector<vector<double>> aug(n, vector<double>(n + 1));
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			aug[i][j] = A[i][j];
		}
		aug[i][n] = B[i];
	}
	for(int i = 0; i < n; ++i) {
		int pivot = -1;
		double mx = 0;
		for(int j = i; j < n; ++j) {
			if(abs(aug[j][i]) > mx) {
				mx = abs(aug[j][i]);
				pivot = j;
			}
		}
		if(pivot == -1 || mx < 1e-10) return {};
		swap(aug[i], aug[pivot]);
		for(int j = i + 1; j < n; ++j) {
			double factor = aug[j][i] / aug[i][i];
			for(int k = i; k <= n; ++k) {
				aug[j][k] -= factor * aug[i][k];
			}
		}
	}
	vector<double> X(n);
	for(int i = n - 1; i >= 0; --i) {
		X[i] = aug[i][n];
		for(int j = i + 1; j < n; ++j) {
			X[i] -= aug[i][j] * X[j];
		}
		X[i] /= aug[i][i];
	}
	return X;
}