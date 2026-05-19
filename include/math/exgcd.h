#pragma once
#include "common.h"

// @returns (gcd, x, y) so that gcd = ax + by
template<class T>
tuple<T, T, T> exgcd(T a, T b) {
	if(b == 0) return tuple(a, 1, 0);
	auto [g, x, y] = exgcd(b, a % b);
	return tuple(g, y, x - (a / b) * y);
}
