#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;

template<class T1, class T2, class F> bool chkf(T1 &x, const T2 &y, F &&f) {
	if(f(static_cast<T1>(y), x)) {
		x = static_cast<T1>(y);
		return true;
	}
	return false;
}
template<class T1, class T2> bool chkmin(T1 &x, const T2 &y) {
	return chkf(x, y, less<T1>{});
}
template<class T1, class T2> bool chkmax(T1 &x, const T2 &y) {
	return chkf(x, y, greater<T1>{});
}

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
		ld theta = 2.l * pi / n * (invert ? -1.l : 1.l);
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
	vector<ld> ret(n);
	for(int i = 0; i < n; ++i) {
		ret[i] = fa[i].real();
	}
	while(ret.size() > (a.size() + b.size() - 1)) {
		ret.pop_back();
	}
	return ret;
}

inline void solve() {}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int t = 1;
	// cin >> t;
	while(t--) {
		solve();
	}
	return 0;
}
