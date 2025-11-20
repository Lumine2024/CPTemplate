#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;

template<class T1, class T2, class F> bool chkf(T1 &x, const T2 &y, F &&f) {
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

constexpr ll modulo = 998244353;
inline ll qpow(ll x, ll n) {
	ll ret = 1;
	for(; n; n >>= 1, x = x * x % modulo)
		if(n & 1) ret = ret * x % modulo;
	return ret;
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
