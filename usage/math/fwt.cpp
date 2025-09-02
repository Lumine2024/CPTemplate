#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

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

constexpr ll modulo = 998244353, inv2 = 499122177;
void fwt_or(vector<ll> &a, bool invert) {
	ll n = a.size(), type = invert ? -1 : 1;
	for(ll x = 2; x <= n; x <<= 1) {
		ll k = x >> 1;
		for(ll i = 0; i < n; i += x) 
			for(ll j = 0; j < k; ++j) 
				a[i + j + k] = (a[i + j + k] + a[i + j] * type) % modulo;
	}
}
void fwt_and(vector<ll> &a, bool invert) {
	ll n = a.size(), type = invert ? -1 : 1;
	for(ll x = 2; x <= n; x <<= 1) {
		ll k = x >> 1;
		for(ll i = 0; i < n; i += x) 
			for(ll j = 0; j < k; ++j) 
				a[i + j] = (a[i + j] + a[i + j + k] * type) % modulo;
	}
}
void fwt_xor(vector<ll> &a, bool invert) {
	ll n = a.size(), type = invert ? inv2 : 1;
	for(ll x = 2; x <= n; x <<= 1) {
		ll k = x >> 1;
		for(ll i = 0; i < n; i += x) {
			for(ll j = 0; j < k; ++j) {
				ll u = a[i + j], v = a[i + j + k];
				a[i + j] = (u + v) % modulo;
				a[i + j + k] = (u - v) % modulo;
				a[i + j] = (a[i + j] * type) % modulo;
				a[i + j + k] = (a[i + j + k] * type) % modulo;
			}
		}
	}
}
void fwt_xnor(vector<ll> &a, bool invert) {
	reverse(a.begin(), a.end());
	fwt_xor(a, invert);
	reverse(a.begin(), a.end());
}
vector<ll> fwt_transform(const vector<ll> &a, const vector<ll> &b, void (*func)(vector<ll> &a, bool invert)) {
	ll n = 1;
	while(n < max(a.size(), b.size())) n <<= 1;
	vector<ll> A(n, 0), B(n, 0), C(n, 0);
	for(ll i = 0; i < a.size(); i++) A[i] = a[i];
	for(ll i = 0; i < b.size(); i++) B[i] = b[i];
	func(A, false);
	func(B, false);
	for(ll i = 0; i < n; i++) {
		C[i] = (A[i] * B[i]) % modulo;
	}
	func(C, true);
	for(ll i = 0; i < n; i++) {
		C[i] = (C[i] % modulo + modulo) % modulo;
	}
	return C;
}

inline void solve() {
	
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int n = 1;
	// cin >> n;
	while(n--) {
		solve();
	}
	return 0;
}