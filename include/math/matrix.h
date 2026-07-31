#pragma once
#include "math/basic.h"

template<class T>
struct Matrix {
	template<class>
	friend struct Matrix;

	Matrix() : n(0), m(0) {}
	Matrix(int _n, int _m) : x(_n * _m), n(_n), m(_m) {}
	template<class U>
	Matrix(const Matrix<U> &o) : x(o.x.begin(), o.x.end()), n(o.n), m(o.m) {}
	static Matrix unit(int _n) {
		Matrix ret(_n, _n);
		for(int i = 0; i < _n; ++i) ret[i][i] = T(1);
		return ret;
	}
	span<T> operator[](int i) {
		return span<T>(x.data() + i * m, m);
	}
	span<const T> operator[](int i) const {
		return span<const T>(x.data() + i * m, m);
	}
	Matrix &operator+=(const Matrix &r) {
		for(int i = 0; i < n * m; ++i) x[i] = x[i] + r.x[i];
		return *this;
	}
	Matrix &operator-=(const Matrix &r) {
		for(int i = 0; i < n * m; ++i) x[i] = x[i] - r.x[i];
		return *this;
	}
	Matrix &operator*=(const Matrix &r) {
		*this = *this * r;
		return *this;
	}
	friend Matrix operator+(const Matrix &l, const Matrix &r) {
		return Matrix(l) += r;
	}
	friend Matrix operator-(const Matrix &l, const Matrix &r) {
		return Matrix(l) -= r;
	}
	friend Matrix operator*(const Matrix &l, const Matrix &r) {
		int rows = l.n, mid = l.m, cols = r.m;
		Matrix ret(rows, cols);
		for(int i = 0; i < rows; ++i) {
			for(int j = 0; j < cols; ++j) {
				for(int k = 0; k < mid; ++k) {
					ret[i][j] = ret[i][j] + l[i][k] * r[k][j];
				}
			}
		}
		return ret;
	}

private:
	vector<T> x;
	int n, m;
};
