#pragma once
#include "common.h"

constexpr ld pi = numbers::pi_v<ld>;

using cd = complex<ld>;
vector<ld> multiply(const vector<ld> &a, const vector<ld> &b) {
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
	auto fft = [](vector<cd> &f, bool inv) -> void {
		int n = f.size();
		for(int i = 1, j = 0; i < n; ++i) {
			int bit = n >> 1;
			for(; (j & bit) != 0; bit >>= 1) j ^= bit;
			j ^= bit;
			if(i < j) swap(f[i], f[j]);
		}
		for(int len = 2; len <= n; len *= 2) {
			ld alp = 2 * pi / len;
			cd wn(cos(alp), sin(alp));
			if(inv) wn.imag(-wn.imag());
			for(int i = 0; i < n; i += len) {
				cd w = 1.0l;
				for(int j = 0; j < len / 2; ++j) {
					cd u = f[i + j], v = f[i + j + len / 2] * w;
					f[i + j] = u + v;
					f[i + j + len / 2] = u - v;
					w *= wn;
				}
			}
		}
	};
	fft(fa, false);
	fft(fb, false);
	for(int i = 0; i < n; ++i) {
		fa[i] *= fb[i];
	}
	fft(fa, true);
	for(int i = 0; i < n; ++i) {
		fa[i] /= n;
	}
	vector<ld> ret(n);
	for(int i = 0; i < n; ++i) {
		ret[i] = fa[i].real();
	}
	while(ret.size() > (a.size() + b.size() - 1)) {
		ret.pop_back();
	}
	return ret;
}
