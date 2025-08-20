#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

inline constexpr ll modulo = 998244353;

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


struct Comb {
	Comb() = delete;
	static ll fact(ll n) {
		return _fact[n];
	}
	static ll invfact(ll n) {
		return _invfact[n];
	}
	static ll binom(ll n, ll m) {
		if(m < 0 || m > n || n < 0) return 0;
		return (((ll(_fact[n]) * ll(_invfact[m])) % modulo) * ll(_invfact[n - m])) % modulo;
	}
private:
	static constexpr int _maxn = 500005;
	static inline int _fact[_maxn], _invfact[_maxn];
	static inline int init = [] {
		_fact[0] = 1;
		for(ll i = 1; i < _maxn; ++i) {
			_fact[i] = (ll(_fact[i - 1]) * i) % modulo;
		}
		_invfact[_maxn - 1] = qpow(_fact[_maxn - 1], modulo - 2);
		for(ll i = _maxn - 2; i >= 0; --i) {
			_invfact[i] = (ll(_invfact[i + 1]) * (i + 1)) % modulo;
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
            _cat[i] = (Comb::binom(2 * i, i) - Comb::binom(2 * i, i - 1) + modulo) % modulo;
        }
        return 0;
    }();
};

inline void solve() {

}

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