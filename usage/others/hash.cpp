
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


struct MyHash {
	size_t operator()(ll x) const noexcept {
		x ^= (x >> 21);
		x ^= (x << 37);
		x ^= (x >> 4);
		x *= 0x27d4eb2f165667c5;
		x ^= (x >> 28);
		x *= 0x165667b19e3779f9;
		x ^= (x >> 31);
		return x ^ c;
	}
private:
	static inline size_t c = (size_t)chrono::steady_clock::now().time_since_epoch().count();
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
