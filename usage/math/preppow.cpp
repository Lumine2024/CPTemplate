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
	ll operator()(ll n) const {
		return pow(n);
	}
	ll operator[](ll n) const {
		return pow(n);
	}

private:
	int m;
	vector<int> powerk, powerkm;
};

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
