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

constexpr ll modulo = 998244353;
constexpr ll qpow(ll x, ll n) {
	ll ret = 1;
	for(; n != 0; n >>= 1, x = x * x % modulo) {
		if(n & 1) ret = ret * x % modulo;
	}
	return ret;
}

ll lagrange(const vector<ll> &x, const vector<ll> &y, ll x0) {
	int n = x.size();
	vector<ll> iden(n);
	for(int i = 0; i < n; ++i) {
		ll den = 1;
		for(int j = 0; j < n; ++j) {
			if(i != j) den = den * (x[i] - x[j] + modulo) % modulo;
		}
		iden[i] = qpow(den, modulo - 2);
	}
	ll ret = 0;
	for(int i = 0; i < n; ++i) {
		ll num = 1;
		for(int j = 0; j < n; ++j) {
			if(i != j) num = num * (x0 - x[j] + modulo) % modulo;
		}
		ret = (ret + y[i] * num % modulo * iden[i]) % modulo;
	}
	return ret;
}

struct Comb {
	Comb() = delete;
	static ll fact(ll n) {
		return fac[n];
	}
	static ll invfact(ll n) {
		return ifac[n];
	}
	static ll perm(ll n, ll m) {
		if(m < 0 || m > n || n < 0) return 0;
		ll fn = fac[n], inm = ifac[n - m];
		return fn * inm % modulo;
	}
	static ll binom(ll n, ll m) {
		if(m < 0 || m > n || n < 0) return 0;
		ll fn = fac[n], im = ifac[m], inm = ifac[n - m];
		return fn * im % modulo * inm % modulo;
	}
private:
	static constexpr int maxn = 500005;
	static inline int fac[maxn], ifac[maxn];
	static inline int init = [] {
		fac[0] = 1;
		for(ll i = 1; i < maxn; ++i) {
			fac[i] = (ll(fac[i - 1]) * i) % modulo;
		}
		ifac[maxn - 1] = qpow(fac[maxn - 1], modulo - 2);
		for(ll i = maxn - 2; i >= 0; --i) {
			ifac[i] = (ll(ifac[i + 1]) * (i + 1)) % modulo;
		}
		return 0;
	}();
};

// if x[i] = i for i = 0 to x.size() - 1, then call this to solve in O(n)
ll lagrange(const vector<ll> &y, ll x0) {
	int n = y.size();
	vector<ll> pre(n), suf(n);
	pre[0] = (x0 - 0 + modulo) % modulo;
	for(int i = 1; i < n; ++i) {
		pre[i] = pre[i - 1] * (x0 - i + modulo) % modulo;
	}
	suf[n - 1] = (x0 - (n - 1) + modulo) % modulo;
	for(int i = n - 2; i >= 0; --i) {
		suf[i] = suf[i + 1] * (x0 - i + modulo) % modulo;
	}
	ll ret = 0;
	for(int i = 0; i < n; ++i) {
		ll term = y[i];
		if(i > 0) term = term * pre[i - 1] % modulo;
		if(i < n - 1) term = term * suf[i + 1] % modulo;
		ll den = Comb::invfact(i) * Comb::invfact(n - 1 - i) % modulo;
		if((n - 1 - i) % 2) den = modulo - den;
		ret = (ret + term * den) % modulo;
	}
	return ret;
}

inline void solve() {
	
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int n = 1;
	// cin >> n;
	for(int i = 0; i < n; ++i) {
		solve();
	}
	return 0;
}