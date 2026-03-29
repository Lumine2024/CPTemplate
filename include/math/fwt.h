#pragma once
#include "preppow.h"

// constexpr ll modulo = 998244353, inv2 = 499122177;
template<ll modulo> void fwt_or(vector<ll> &a, bool invert) {
	constexpr ll inv2 = qpow<modulo>(2, modulo - 2);
	ll n = a.size(), type = invert ? -1 : 1;
	for(ll x = 2; x <= n; x <<= 1) {
		ll k = x >> 1;
		for(ll i = 0; i < n; i += x)
			for(ll j = 0; j < k; ++j)
				a[i + j + k] = (a[i + j + k] + a[i + j] * type) % modulo;
	}
}
template<ll modulo> void fwt_and(vector<ll> &a, bool invert) {
	constexpr ll inv2 = qpow<modulo>(2, modulo - 2);
	ll n = a.size(), type = invert ? -1 : 1;
	for(ll x = 2; x <= n; x <<= 1) {
		ll k = x >> 1;
		for(ll i = 0; i < n; i += x)
			for(ll j = 0; j < k; ++j)
				a[i + j] = (a[i + j] + a[i + j + k] * type) % modulo;
	}
}
template<ll modulo> void fwt_xor(vector<ll> &a, bool invert) {
	constexpr ll inv2 = qpow<modulo>(2, modulo - 2);
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
template<ll modulo> void fwt_xnor(vector<ll> &a, bool invert) {
	constexpr ll inv2 = qpow<modulo>(2, modulo - 2);
	reverse(a.begin(), a.end());
	fwt_xor(a, invert);
	reverse(a.begin(), a.end());
}
template<ll modulo>
vector<ll> fwt_transform(const vector<ll> &a, const vector<ll> &b,
						 void (*func)(vector<ll> &a, bool invert)) {
	constexpr ll inv2 = qpow<modulo>(2, modulo - 2);
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
