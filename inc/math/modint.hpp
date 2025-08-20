#pragma once
#include "constants.hpp"

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
private:
	int m;
	vector<int> powerk, powerkm;
};

struct ModInt {
	ModInt(ll v = 0) : val(v % modulo) {
		if(val < 0) val += modulo;
	}
	ModInt operator+(const ModInt &rhs) const {
		ll retval = val + rhs.val;
		if(retval >= modulo) retval -= modulo;
		return ModInt(retval, true);
	}
	ModInt operator-(const ModInt &rhs) const {
		ll retval = val - rhs.val;
		if(retval < 0) retval += modulo;
		return ModInt(retval, true);
	}
	ModInt operator*(const ModInt &rhs) const {
		return ModInt(val * rhs.val % modulo, true);
	}
	ModInt operator/(const ModInt &rhs) const {
		return ModInt(val * qpow(rhs.val, modulo - 2) % modulo, true);
	}
	ModInt power(int n) const {
		ModInt ret = 1;
		for(ModInt base = val; n != 0; n >>= 1, base = base * base) {
			if(n & 1) ret = ret * base;
		}
		return ret;
	}
	operator ll() const {
		return val;
	}
private:
	ll val;
	ModInt(ll v, bool) : val(v) {}
};