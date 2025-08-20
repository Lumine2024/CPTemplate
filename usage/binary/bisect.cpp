// Standalone C++ file generated from binary/bisect.hpp
// Can be directly submitted to online judges

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;

inline constexpr ll modulo = 998244353, g = 3, inf = 0x3f3f3f3f3f3f3f3f;
inline constexpr int maxn = 100005, infint = 0x3f3f3f3f;
inline constexpr ld eps = 1e-9l, pi = 3.14159265358979323846264338327950288l, infld = 1e12l;

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

// === binary/bisect.hpp ===

template<class T> constexpr T defminv = T{};
template<class T> constexpr T defmaxv = T{};
template<class T> constexpr T defeps = T{};
template<class T> constexpr T defdelta = T{};
template<signed_integral T> constexpr T defminv<T> = numeric_limits<T>::min() / 2;
template<signed_integral T> constexpr T defmaxv<T> = numeric_limits<T>::max() / 2;
template<signed_integral T> constexpr T defeps<T> = 0;
template<signed_integral T> constexpr T defdelta<T> = 1;
template<unsigned_integral T> constexpr T defminv<T> = 0;
template<unsigned_integral T> constexpr T defmaxv<T> = numeric_limits<T>::max() / 2;
template<unsigned_integral T> constexpr T defeps<T> = 0;
template<unsigned_integral T> constexpr T defdelta<T> = 1;
template<floating_point T> constexpr T defminv<T> = -1e12;
template<floating_point T> constexpr T defmaxv<T> = 1e12;
template<floating_point T> constexpr T defeps<T> = 1e-9;
template<floating_point T> constexpr T defdelta<T> = 1e-9;

template<class T> T binary(auto &&check, T minv = defminv<T>, T maxv = defmaxv<T>, T eps = defeps<T>, T delta = defdelta<T>) {
	T ans{}, hi = maxv, lo = minv;
	while((maxv - minv) > eps) {
		T mid = (minv + maxv) / 2;
		if(check(mid)) {
			ans = mid;
			hi = mid - delta;
		} else {
			lo = mid + delta;
		}
	}
	return ans;
}

// Example usage:
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
