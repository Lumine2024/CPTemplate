
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;

inline constexpr ll modulo = 998244353;

inline ll qpow(ll x, ll n) {
	ll ret = 1;
	for(; n != 0; n >>= 1, x = x * x % modulo) {
		if(n & 1) ret = ret * x % modulo;
	}
	return ret;
}

template<class T, class F> concept binary_func = convertible_to<F, function<bool(T, T)>>;
template<class T1, class T2, class F> requires(binary_func<T1, F> &&convertible_to<T2, T1>) bool chkf(T1 &x, const T2 &y, F &&f) {
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

struct Comb {
	Comb() = delete;
	static ll fact(ll n) {
		return fac[n];
	}
	static ll invfact(ll n) {
		return ifac[n];
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
