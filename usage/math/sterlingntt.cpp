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

vector<ll> sterling_ntt(int k) {
	if(k == 0) return {1};
	vector<ll> powk(k + 1, 0);
	powk[1] = 1;
	vector<bool> isprime(k + 1, true);
	isprime[0] = isprime[1] = false;
	vector<int> primes;
	for(int i = 2; i <= k; ++i) {
		if(isprime[i]) {
			primes.push_back(i);
			powk[i] = qpow(i, k);
		}
		for(ll p : primes) {
			ll q = i * p;
			if(q > k) break;
			isprime[q] = false;
			powk[q] = powk[i] * powk[p] % modulo;
			if(i % p == 0) break;
		}
	}
	vector<ll> fact(k + 1), invfact(k + 1);
	fact[0] = fact[1] = 1;
	for(ll i = 2; i <= k; ++i) {
		fact[i] = fact[i - 1] * i % modulo;
	}
	invfact[k] = qpow(fact[k], modulo - 2);
	for(int i = k - 1; i >= 0; --i) {
		invfact[i] = invfact[i + 1] * (i + 1) % modulo;
	}
	int n = 1;
	while(n < (2 * k + 1)) {
		n <<= 1;
	}
	vector<ll> a(n, 0), b(n, 0);
	for(int i = 0; i <= k; ++i) {
		a[i] = powk[i] * invfact[i] % modulo;
		if(i % 2 == 1) {
			b[i] = (modulo - invfact[i]) % modulo;
		} else {
			b[i] = invfact[i];
		}
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
		for(int i = 0; i < n / 2; ++i) {
			ll u = f0[i];
			ll v = w * f1[i] % modulo;
			f[i] = (u + v) % modulo;
			f[i + n / 2] = (u - v + modulo) % modulo;
			w = w * wn % modulo;
		}
	};
	ntt(ntt, a, false);
	ntt(ntt, b, false);
	vector<ll> c(n);
	for(int i = 0; i < n; ++i) {
		c[i] = a[i] * b[i] % modulo;
	}
	ntt(ntt, c, true);
	ll invn = qpow(n, modulo - 2);
	for(int i = 0; i < n; ++i) {
		c[i] = c[i] * invn % modulo;
	}
	c.resize(k + 1);
	return c;
}

inline void solve() {
	
}

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
