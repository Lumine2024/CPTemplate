
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;

inline constexpr ll modulo = 998244353, g = 3, inf = 0x3f3f3f3f3f3f3f3f;
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


struct Sterling {
	Sterling() = delete;
	static int get(int n, int m) {
		return ster[n][m];
	}
private:
	static constexpr int maxn = 5005;
	static inline int ster[maxn][maxn];
	static inline int init = [] {
		ster[0][0] = 1;
		for(ll i = 1; i < maxn; ++i) {
			ster[i][0] = 0;
			for(ll j = 1; j < i; ++j) {
				ster[i][j] = (ll(ster[i - 1][j - 1]) + ll(ster[i - 1][j]) * j) % modulo;
			}
		}
		return 0;
	}();
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
