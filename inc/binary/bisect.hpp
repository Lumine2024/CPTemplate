#pragma once
#include "../constants.hpp"

template<class T> constexpr T defminv = T{};
template<class T> constexpr T defmaxv = T{};
template<class T> constexpr T defeps = T{};
template<class T> constexpr T defdelta = T{};
template<signed_integral T> constexpr T defminv<T> = numeric_limits<T>::min() / 2;
template<signed_integral T> constexpr T defmaxv<T> = numeric_limits<T>::max() / 2;
template<signed_integral T> constexpr T defeps<T> = 0;
template<signed_integral T> constexpr T defdelta<T> = 1;
template<unsigned_integral T> constexpr T defminv<T> = 0;
template<unsigned_integral T> constexpr T defmaxv<T> = numeric_limits<T>::max() / 2;
template<unsigned_integral T> constexpr T defeps<T> = 0;
template<unsigned_integral T> constexpr T defdelta<T> = 1;
template<floating_point T> constexpr T defminv<T> = -1e12;
template<floating_point T> constexpr T defmaxv<T> = 1e12;
template<floating_point T> constexpr T defeps<T> = 1e-9;
template<floating_point T> constexpr T defdelta<T> = 1e-9;

template<class T> T binary(auto &&check, T minv = defminv<T>, T maxv = defmaxv<T>, T eps = defeps<T>, T delta = defdelta<T>) {
	T ans{}, hi = maxv, lo = minv;
	while((maxv - minv) > eps) {
		T mid = (minv + maxv) / 2;
		if(check(mid)) {
			ans = mid;
			hi = mid - delta;
		} else {
			lo = mid + delta;
		}
	}
	return ans;
}