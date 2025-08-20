
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;

inline constexpr ll modulo = 998244353, inf = 0x3f3f3f3f3f3f3f3f;

inline ll qpow(ll x, ll n) {
    ll ret = 1;
    for(; n != 0; n >>= 1, x = x * x % modulo) {
        if(n & 1) ret = ret * x % modulo;
    }
    return ret;
}

template<class T, class F> bool chkf(T &x, const T &y, F &&f) {
    if(f(y, x)) {
        x = y;
        return true;
    }
    return false;
}
template<class T> bool chkmin(T &x, const T &y) {
    return chkf(x, y, less{});
}
template<class T> bool chkmax(T &x, const T &y) {
    return chkf(x, y, greater{});
}


ll __qpow(ll x, ll n) {
	ll ret = 1;
	for(; n != 0; n >>= 1, x = x * x) {
		if(n & 1) ret = ret * x;
	}
	return ret;
}

template<class F> concept eularsieve_func = convertible_to<F, function<ll(int, int)>>;

struct EularSieve {
	vector<int> primes, lpf, lpow;
	vector<ll> fv;

	explicit EularSieve(int n) : lpf(n + 1), lpow(n + 1) {
		for(ll i = 2; i <= n; ++i) {
			if(lpf[i] == 0) {
				lpf[i] = i;
				lpow[i] = 1;
				primes.push_back(i);
			}
			for(ll p : primes) {
				ll j = i * p;
				if(j > n) break;
				lpf[j] = p;
				if(i % p == 0) {
					lpow[j] = lpow[i] + 1;
					ll jp = __qpow(lpf[j], lpow[j]);
					ll rem = j / jp;
					break;
				} else {
					lpow[j] = 1;
				}
			}
		}
	}

	template<eularsieve_func F> EularSieve(int n, F &&f) : lpf(n + 1), lpow(n + 1), fv(n + 1) {
		fv[1] = 1;
		for(ll i = 2; i <= n; ++i) {
			if(lpf[i] == 0) {
				lpf[i] = i;
				lpow[i] = 1;
				primes.push_back(i);
				fv[i] = f(i, 1);
			}
			for(ll p : primes) {
				ll j = i * p;
				if(j > n) break;
				lpf[j] = p;
				if(i % p == 0) {
					lpow[j] = lpow[i] + 1;
					ll jp = __qpow(lpf[j], lpow[j]);
					ll rem = j / jp;
					if(rem == 1) {
						fv[j] = f(p, lpow[j]);
					} else {
						fv[j] = fv[rem] * fv[jp];
					}
					break;
				} else {
					fv[j] = fv[i] * fv[p];
					lpow[j] = 1;
				}
			}
		}
	}
};

int eular_f(int p, int k) {
	return __qpow(p, k) - __qpow(p, k - 1);
}
int mobius_f(int p, int k) {
	return k == 0 ? 1 : k == 1 ? -1 : 0;
}
int factor_cnt_f(int p, int k) {
	return k + 1;
}
int factor_sum_f(int p, int k) {
	return (__qpow(p, k + 1) - 1ll) / ll(p - 1);
}

inline void solve() {
    // Add your solution code here using the template above
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
