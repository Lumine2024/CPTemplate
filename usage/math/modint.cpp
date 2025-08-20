
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;

inline constexpr ll modulo = 998244353, inf = 0x3f3f3f3f3f3f3f3f;
inline constexpr int maxn = 100005, infint = 0x3f3f3f3f;

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


struct PreprocessedPow {
	PreprocessedPow(ll k, ll maxn) {
		k %= modulo;
		m = ceil(sqrt(maxn + 1.5));
		powerk.assign(m, 1);
		powerkm.assign(m, 1);
		for(int i = 1; i < m; ++i) {
			powerk[i] = (ll(powerk[i - 1]) * k) % modulo;
		}
		powerkm[1] = ll(powerk[m - 1]) * k % modulo;
		for(int i = 2; i < m; ++i) {
			powerkm[i] = ll(powerkm[i - 1]) * ll(powerkm[1]) % modulo;
		}
	}
	ll pow(ll n) const {
		ll i = n / m, j = n % m;
		return (ll(powerkm[i]) * ll(powerk[j])) % modulo;
	}
private:
	int m;
	vector<int> powerk, powerkm;
};

struct ModInt {
	ModInt(ll v = 0) : val(v % modulo) {
		if(val < 0) val += modulo;
	}
	ModInt operator+(const ModInt &rhs) const {
		ll retval = val + rhs.val;
		if(retval >= modulo) retval -= modulo;
		return ModInt(retval, true);
	}
	ModInt operator-(const ModInt &rhs) const {
		ll retval = val - rhs.val;
		if(retval < 0) retval += modulo;
		return ModInt(retval, true);
	}
	ModInt operator*(const ModInt &rhs) const {
		return ModInt(val * rhs.val % modulo, true);
	}
	ModInt operator/(const ModInt &rhs) const {
		return ModInt(val * qpow(rhs.val, modulo - 2) % modulo, true);
	}
	ModInt power(int n) const {
		ModInt ret = 1;
		for(ModInt base = val; n != 0; n >>= 1, base = base * base) {
			if(n & 1) ret = ret * base;
		}
		return ret;
	}
	operator ll() const {
		return val;
	}
private:
	ll val;
	ModInt(ll v, bool) : val(v) {}
};

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
