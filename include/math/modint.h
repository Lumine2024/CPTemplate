#pragma once
#include "math/basic.h"

template<unsigned M>
struct ModInt {
	static constexpr unsigned modulo = M;
	ModInt() : val(0) {}
	ModInt(ll x) : val(norm<modulo>(x)) {}
	ModInt &operator+=(const ModInt &z) {
		val += z.val;
		if(val >= modulo) val -= modulo;
		return *this;
	}
	ModInt &operator-=(const ModInt &z) {
		if(val < z.val) val += modulo;
		val -= z.val;
		return *this;
	}
	ModInt &operator*=(const ModInt &z) {
		val = (ll)val * z.val % modulo;
		return *this;
	}
	ModInt &to_inv() {
		val = qpow<modulo>(val, modulo - 2);
		return *this;
	}
	ModInt inv() const {
		ModInt z = *this;
		return z.to_inv();
	}
	friend ModInt operator+(const ModInt &a, const ModInt &b) {
		ModInt c = a;
		return c += b;
	}
	friend ModInt operator-(const ModInt &a, const ModInt &b) {
		ModInt c = a;
		return c -= b;
	}
	friend ModInt operator*(const ModInt &a, const ModInt &b) {
		ModInt c = a;
		return c *= b;
	}
	friend bool operator==(const ModInt &a, const ModInt &b) = default;
	operator unsigned() const {
		return val;
	}

private:
	unsigned val;
};
