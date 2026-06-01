#include "math/fwt.h"
#include "doctest.h"

constexpr ll mod = 998244353;

static ll norm(ll x) {
	x %= mod;
	if(x < 0) x += mod;
	return x;
}

static vector<ll> brute_or_conv(const vector<ll> &a, const vector<ll> &b) {
	int n = (int)a.size();
	vector<ll> c(n, 0);
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			c[i | j] = (c[i | j] + a[i] * b[j]) % mod;
		}
	}
	for(ll &x : c) x = norm(x);
	return c;
}

static vector<ll> brute_and_conv(const vector<ll> &a, const vector<ll> &b) {
	int n = (int)a.size();
	vector<ll> c(n, 0);
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			c[i & j] = (c[i & j] + a[i] * b[j]) % mod;
		}
	}
	for(ll &x : c) x = norm(x);
	return c;
}

static vector<ll> brute_xor_conv(const vector<ll> &a, const vector<ll> &b) {
	int n = (int)a.size();
	vector<ll> c(n, 0);
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			c[i ^ j] = (c[i ^ j] + a[i] * b[j]) % mod;
		}
	}
	for(ll &x : c) x = norm(x);
	return c;
}

static vector<ll> brute_xnor_conv(const vector<ll> &a, const vector<ll> &b) {
	int n = (int)a.size();
	int mask = n - 1;
	vector<ll> c(n, 0);
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			int idx = mask ^ (i ^ j);
			c[idx] = (c[idx] + a[i] * b[j]) % mod;
		}
	}
	for(ll &x : c) x = norm(x);
	return c;
}

TEST_CASE("fwt_or_transform_matches_bruteforce") {
	vector<ll> a = {1, 2, 3, 4};
	vector<ll> b = {5, 6, 7, 8};
	auto c = fwt_transform<mod>(a, b, fwt_or<mod>);
	REQUIRE(c == brute_or_conv(a, b));
}

TEST_CASE("fwt_and_transform_matches_bruteforce") {
	vector<ll> a = {9, 0, 2, 1};
	vector<ll> b = {3, 4, 5, 6};
	auto c = fwt_transform<mod>(a, b, fwt_and<mod>);
	REQUIRE(c == brute_and_conv(a, b));
}

TEST_CASE("fwt_xor_transform_matches_bruteforce") {
	vector<ll> a = {3, 1, 4, 1, 5, 9, 2, 6};
	vector<ll> b = {5, 3, 5, 8, 9, 7, 9, 3};
	auto c = fwt_transform<mod>(a, b, fwt_xor<mod>);
	REQUIRE(c == brute_xor_conv(a, b));
}

TEST_CASE("fwt_xnor_transform_matches_bruteforce") {
	vector<ll> a = {10, 20, 30, 40};
	vector<ll> b = {1, 3, 5, 7};
	auto c = fwt_transform<mod>(a, b, fwt_xnor<mod>);
	REQUIRE(c == brute_xnor_conv(a, b));
}
