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

constexpr ll modulo = 998244353, g = 3;
inline ll qpow(ll x, ll n) {
	ll ret = 1;
	for(; n; n >>= 1, x = x * x % modulo)
		if(n & 1) ret = ret * x % modulo;
	return ret;
}

vector<ll> multiply(const vector<ll> &a, const vector<ll> &b) {
	int n = 1;
	while(n < a.size() + b.size()) {
		n <<= 1;
	}
	vector<ll> ca(n), cb(n);
	for(int i = 0; i < a.size(); ++i) {
		ca[i] = a[i];
	}
	for(int i = 0; i < b.size(); ++i) {
		cb[i] = b[i];
	}
	auto ntt = [](auto &&ntt, vector<ll> &f, bool invert) -> void {
		int n = f.size();
		if(n == 1) return;
		vector<ll> f0(n / 2), f1(n / 2);
		for(int i = 0; i < n / 2; ++i) {
			f0[i] = f[2 * i];
			f1[i] = f[2 * i + 1];
		}
		ntt(ntt, f0, invert);
		ntt(ntt, f1, invert);
		ll w = 1, wn = qpow(g, (modulo - 1) / n);
		if(invert) {
			wn = qpow(wn, modulo - 2);
		}
		for(int t = 0; t < n / 2; ++t) {
			ll u = f0[t], v = w * f1[t] % modulo;
			f[t] = (u + v) % modulo;
			f[t + n / 2] = (u - v + modulo) % modulo;
			w = w * wn % modulo;
		}
	};
	ntt(ntt, ca, false);
	ntt(ntt, cb, false);
	for(int i = 0; i < n; ++i) {
		ca[i] = ca[i] * cb[i] % modulo;
	}
	ntt(ntt, ca, true);
	for(int i = 0; i < n; ++i) {
		ca[i] = ca[i] * qpow(n, modulo - 2) % modulo;
	}
	while(ca.size() > (a.size() + b.size() - 1)) {
		ca.pop_back();
	}
	return ca;
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
