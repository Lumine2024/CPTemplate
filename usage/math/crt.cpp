
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

// @returns (gcd, x, y) so that gcd = ax + by
tuple<ll, ll, ll> exgcd(ll a, ll b) {
	if(b == 0) return tuple(a, 1, 0);
	auto [g, x, y] = exgcd(b, a % b);
	return tuple(g, y, x - (a / b) * y);
}


// @returns (a, b) so that answer is a + kb, k\in N_+
pair<ll, ll> crt(const vector<ll> &rem, const vector<ll> &mod) {
	int n = rem.size();
	ll modulo_ = 1, ans = 0;
	for(int i = 0; i < n; ++i) {
		modulo_ *= mod[i];
	}
	for(int i = 0; i < n; ++i) {
		ll m = modulo_ / mod[i];
		auto [_, b, __] = exgcd(m, mod[i]);
		ans = (ans + ((rem[i] * m) % modulo_ * b) % modulo_) % modulo_;
	}
	return pair((ans % modulo_ + modulo_) % modulo_, modulo_);
}

pair<ll, ll> excrt(const vector<ll> &rem, const vector<ll> &mod) {
	int n = rem.size();
	ll r1 = rem[0], m1 = mod[0];
	for(int i = 1; i < n; ++i) {
		ll r2 = rem[i], m2 = mod[i];
		auto [g, p, _] = exgcd(m1, m2);
		if((r2 - r1) % g != 0) {
			return { -1, -1 };
		}
		ll v = m2 / g, x = (r2 - r1) / g;
		ll u = p % v * x % v;
		ll w = (u % v + v) % v;
		r1 += w * m1;
		m1 = lcm(m1, m2);
	}
	return { (r1 % m1 + m1) % m1, m1 };
}

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
