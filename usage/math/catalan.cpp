#include "../common.h"

constexpr ll modulo = 998244353;
ll qpow(ll x, ll n) {
	ll ret = 1;
	for(; n; n >>= 1, x = x * x % modulo)
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
	static ll binom(ll n, ll m) {
		if(m < 0 || m > n || n < 0) return 0;
		return (((ll(fac[n]) * ll(ifac[m])) % modulo) * ll(ifac[n - m])) %
			   modulo;
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

struct Catalan {
	Catalan() = delete;
	static ll get(int x) {
		return _cat[x];
	}

private:
	static constexpr int _maxn = 250005;
	static inline int _cat[_maxn];
	static inline int init = [] {
		_cat[0] = 1;
		for(int i = 1; i < _maxn; ++i) {
			_cat[i] =
				(Comb::binom(2 * i, i) - Comb::binom(2 * i, i - 1) + modulo) %
				modulo;
		}
		return 0;
	}();
};

inline void solve() {}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int n = 1;
	// cin >> n;
	while(n--) {
		solve();
	}
	return 0;
}