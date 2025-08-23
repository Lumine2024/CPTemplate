#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;

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

template<class F> concept check_function = convertible_to<F, function<bool(int)>>;

template<class T, check_function F> T binary(F &&check, bool rev = false, T minv = defminv<T>, T maxv = defmaxv<T>, T eps = defeps<T>, T delta = defdelta<T>) {
    T ans = (rev ? minv : maxv), hi = maxv, lo = minv;
    while((hi - lo) >= eps) {
        T mid = (lo + hi) / 2;
        if(check(mid)) {
            ans = mid;
            rev ? (lo = mid + delta) : (hi = mid - delta);
        } else {
            rev ? (hi = mid - delta) : (lo = mid + delta);
        }
    }
    return ans;
}

inline void solve() {
    
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    for(int i = 0; i < t; ++i) {
        solve();
    }
    return 0;
}
