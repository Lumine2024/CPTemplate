#include "common.h"

constexpr ll modulo = 998244353;
inline ll qpow(ll x, ll n) {
	ll ret = 1;
	for(; n; n >>= 1, x = x * x % modulo)
		if(n & 1) ret = ret * x % modulo;
	return ret;
}

// 要计算\sum floor(n/i)
ll intdiv(ll n) {
	ll ans = 0;
	for(ll b = 1; b <= n;) {
		ll val = n / b;
		ll r = n / val;
		ll len = r - b + 1;
		ans = (ans + (len % modulo * val % modulo)) % modulo;
		b = r + 1;
	}
	return ans;
}

inline void solve() {}

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
