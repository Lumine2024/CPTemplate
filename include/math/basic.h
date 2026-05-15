#pragma once
#include "common.h"

template<ll modulo>
constexpr ll norm(ll x) {
	x %= modulo;
	if(x < 0) x += modulo;
	return x;
}

template<ll modulo>
constexpr ll qpow(ll x, ll n) {
	x = norm<modulo>(x);
	ll ret = 1;
	for(; n != 0; n >>= 1, x = x * x % modulo) {
		if(n & 1) ret = ret * x % modulo;
	}
	return ret;
}

constexpr ll ipow(ll x, ll n) {
	ll ret = 1;
	for(; n != 0; n >>= 1, x *= x) {
		if(n & 1) ret *= x;
	}
	return ret;
}
