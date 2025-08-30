
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
