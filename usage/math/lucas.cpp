#include "../common.h"

struct Lucas {
	explicit Lucas(int m) : modulo(m), fact(m + 1, 1), invfact(m + 1, 1) {
		for(ll i = 1; i <= m; ++i) {
			fact[i] = (ll)fact[i - 1] * i % modulo;
		}
		invfact[m] = qpow(fact[m], modulo - 2);
		for(ll i = m - 1; i >= 0; --i) {
			invfact[i] = ll(invfact[i + 1]) * (i + 1) % modulo;
		}
	}
	int binom(ll n, ll m) const {
		auto _binom = [&](int n, int m) -> ll {
			if(m < 0 || m > n) return 0;
			return ll(fact[n]) * ll(invfact[m]) * ll(invfact[n - m]) % modulo;
		};
		if(m == 0) return 1;
		return ll(binom(n / modulo, m / modulo)) *
			   _binom(n % modulo, m % modulo) % modulo;
	}

private:
	int modulo;
	vector<int> fact, invfact;
	ll qpow(ll x, ll n) const {
		ll ret = 1;
		for(; n != 0; n >>= 1, x = x * x % modulo) {
			if(n & 1) ret = ret * x % modulo;
		}
		return ret;
	}
};

inline void solve() {
	int n, m, p;
	cin >> n >> m >> p;
	Lucas l(p);
	cout << l.binom(n, m) << '\n';
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int n = 1;
	cin >> n;
	while(n--) {
		solve();
	}
	return 0;
}