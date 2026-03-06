#include "common.h"

inline constexpr ll modulo = 998244353;
constexpr ll qpow(ll x, ll n) {
	ll ret = 1;
	for(; n != 0; n >>= 1, x = x * x % modulo)
		if(n & 1) ret = ret * x % modulo;
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
