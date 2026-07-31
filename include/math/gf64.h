#pragma once
#include "math/basic.h"

struct GF64 {
	GF64(ull _v = 0) : v(_v) {}
	GF64 operator+(GF64 o) const {
		return GF64(v ^ o.v);
	}
	GF64 &operator+=(GF64 o) {
		v ^= o.v;
		return *this;
	}
	GF64 operator*(GF64 o) const {
		ull a = v, b = o.v, r = 0;
		for(; b > 0; b >>= 1, a = (a << 1) ^ (a >> 63 ? 27 : 0))
			if((b & 1) == 1) r ^= a;
		return r;
	}
	GF64 qpow(ull e) const {
		GF64 r = 1, a = *this;
		for(; e > 0; e >>= 1, a = a * a)
			if((e & 1) == 1) r = r * a;
		return r;
	}
	GF64 inv() const {
		return qpow(~0ULL - 1);
	}
	ull val() const {
		return v;
	}

private:
	ull v;
};
