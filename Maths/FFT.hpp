#pragma once
#include <bits/stdc++.h>
#include "Constants.hpp"
using namespace std;
using ll = long long;
using ull = unsigned long long;

using cd = complex<double>;
vector<int> multiply(const vector<int> &a, const vector<int> &b) {
	int n = 1;
	while(n < (a.size() + b.size())) {
		n <<= 1;
	}
	vector<cd> fa(n), fb(n);
	for(int i = 0; i < a.size(); ++i) {
		fa[i] = a[i];
	}
	for(int i = 0; i < b.size(); ++i) {
		fb[i] = b[i];
	}
	auto fft = [](auto &&fft, vector<cd> &f, bool invert) -> void {
		int n = f.size();
		if(n == 1) return;
		vector<cd> f0(n / 2), f1(n / 2);
		for(int i = 0; i < n / 2; ++i) {
			f0[i] = f[2 * i];
			f1[i] = f[2 * i + 1];
		}
		fft(fft, f0, invert);
		fft(fft, f1, invert);
		double theta = 2.l * pi / n * (invert ? -1.l : 1.l);
		cd wt = 1, w(cos(theta), sin(theta));
		for(int t = 0; t < n / 2; ++t) {
			cd u = f0[t], v = wt * f1[t];
			f[t] = u + v;
			f[t + n / 2] = u - v;
			wt *= w;
		}
	};
	fft(fft, fa, false);
	fft(fft, fb, false);
	for(int i = 0; i < n; ++i) {
		fa[i] *= fb[i];
	}
	fft(fft, fa, true);
	for(int i = 0; i < n; ++i) {
		fa[i] /= n;
	}
	vector<int> ret(n);
	for(int i = 0; i < n; ++i) {
		ret[i] = int(fa[i].real() + (fa[i].real() > 0.l ? 0.5l : -0.5l));
	}
	while(ret.size() > (a.size() + b.size() - 1)) {
		ret.pop_back();
	}
	return ret;
}