#pragma once
#include "math/modint.h"

template<unsigned M>
optional<vector<vector<ModInt<M>>>> gauss(const vector<vector<ModInt<M>>> &a,
										  const vector<vector<ModInt<M>>> &b) {
	using Z = ModInt<M>;
	int r = a.size(), n = a[0].size(), m = b[0].size(), row = 0;
	vector<vector<Z>> aug(r, vector<Z>(n + m));
	for(int i = 0; i < r; ++i) {
		for(int j = 0; j < m + n; ++j) {
			aug[i][j] = (j < n) ? a[i][j] : b[i][j - n];
		}
	}
	vector<int> where(n, -1);
	for(int col = 0; col < n && row < r; ++col) {
		int sel = row;
		while(sel < r && aug[sel][col] == Z(0)) ++sel;
		if(sel == r) continue;
		swap(aug[row], aug[sel]);
		Z inv = aug[row][col].inv();
		for(int j = col; j < n + m; ++j) {
			aug[row][j] *= inv;
		}
		for(int i = 0; i < r; ++i) {
			if(i != row && aug[i][col] != Z(0)) {
				Z f = aug[i][col];
				for(int j = col; j < n + m; ++j) {
					aug[i][j] -= f * aug[row][j];
				}
			}
		}
		where[col] = row;
		++row;
	}
	for(int i = row; i < r; ++i) {
		bool flag = true;
		for(int j = 0; j < n; ++j) {
			if(aug[i][j] != Z(0)) {
				flag = false;
				break;
			}
		}
		if(flag) {
			for(int j = 0; j < m; ++j) {
				if(aug[i][n + j] != Z(0)) return nullopt;
			}
		}
	}
	for(int col = 0; col < n; ++col) {
		if(where[col] == -1) return nullopt;
	}
	vector<vector<Z>> ret(n, vector<Z>(m));
	for(int col = 0; col < n; ++col) {
		for(int j = 0; j < m; ++j) {
			ret[col][j] = aug[where[col]][n + j];
		}
	}
	return ret;
}

template<unsigned M>
ModInt<M> det(vector<vector<ModInt<M>>> &mat) {
	using Z = ModInt<M>;
	int n = mat.size();
	Z ans = Z(1);
	for(int row = 0; row < n; ++row) {
		int sel = row;
		while(sel < n && mat[sel][row] == Z(0)) ++sel;
		if(sel == n) return Z(0);
		if(sel != row) {
			swap(mat[sel], mat[row]);
			ans = Z(0) - ans;
		}
		Z inv = mat[row][row].inv();
		ans *= mat[row][row];
		for(int j = row + 1; j < n; ++j) {
			Z delta = mat[j][row] * inv;
			for(int k = row; k < n; ++k) {
				mat[j][k] -= delta * mat[row][k];
			}
		}
	}
	return ans;
}
