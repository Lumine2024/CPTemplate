#pragma once
#include "math/ntt.h"

template<unsigned X>
	requires(g<X> != 0)
struct Polynomial {
	using Z = ModInt<X>;
	Polynomial() {}
	template<class U>
	Polynomial(const vector<U> &val) : a(val.begin(), val.end()) {}
	template<class U>
	Polynomial(initializer_list<U> val) : a(val.begin(), val.end()) {}
	int size() const {
		return a.size();
	}
	bool empty() const {
		return a.empty();
	}
	Z &operator[](int idx) {
		return a[idx];
	}
	Z operator[](int idx) const {
		return a[idx];
	}
	Polynomial &to_mod_xk(int k) {
		if(k <= 0) {
			a.clear();
		} else if(a.size() > k) {
			a.resize(k);
		}
		return *this;
	}
	Polynomial mod_xk(int k) const {
		auto b = *this;
		return b.to_mod_xk(k);
	}
	Polynomial &to_deriv() {
		if(a.empty()) return *this;
		for(int i = 1; i < a.size(); ++i) {
			a[i - 1] = a[i] * Z(i);
		}
		a.pop_back();
		return *this;
	}
	Polynomial deriv() const {
		auto b = *this;
		return b.to_deriv();
	}
	Polynomial &to_integ() {
		a.push_back(Z(0));
		for(int i = a.size() - 1; i > 0; --i) {
			a[i] = a[i - 1] * Z(i).inv();
		}
		a[0] = 0;
		return *this;
	}
	Polynomial integ() const {
		auto b = *this;
		return b.to_integ();
	}
	Polynomial inv(int m) const {
		Polynomial x{a[0].inv()};
		int k = 1;
		while(k < m) {
			k *= 2;
			x = x * (Polynomial{2} - mod_xk(k) * x);
			x.to_mod_xk(k);
		}
		return x.to_mod_xk(m);
	}
	Polynomial ln(int m) const {
		return (deriv() * inv(m)).to_integ().to_mod_xk(m);
	}
	Polynomial exp(int m) const {
		Polynomial x{1};
		int k = 1;
		while(k < m) {
			k *= 2;
			x *= Polynomial{1} - x.ln(k) + mod_xk(k);
			x.to_mod_xk(k);
		}
		return x.to_mod_xk(m);
	}
	Polynomial sqrt(int m) const {
		Polynomial x{1};
		int k = 1;
		while(k < m) {
			k *= 2;
			x = (x + mod_xk(k) * x.inv(k));
			x.to_mod_xk(k);
			x *= (Z::modulo + 1) / 2;
		}
		return x.to_mod_xk(m);
	}
	Polynomial &operator+=(const Polynomial &b) {
		if(a.size() < b.a.size()) {
			a.resize(b.a.size(), Z{});
		}
		for(int i = 0; i < b.a.size(); ++i) {
			a[i] += b.a[i];
		}
		return *this;
	}
	Polynomial &operator-=(const Polynomial &b) {
		if(a.size() < b.a.size()) {
			a.resize(b.a.size(), Z{});
		}
		for(int i = 0; i < b.a.size(); ++i) {
			a[i] -= b.a[i];
		}
		return *this;
	}
	Polynomial &operator*=(const Polynomial &b) {
		a = multiply(a, b.a);
		return *this;
	}
	Polynomial &operator*=(Z k) {
		for(Z &i : a) i *= k;
		return *this;
	}
	Polynomial operator+(const Polynomial &b) const {
		auto c = *this;
		return c += b;
	}
	Polynomial operator-(const Polynomial &b) const {
		auto c = *this;
		return c -= b;
	}
	Polynomial operator*(const Polynomial &b) const {
		return Polynomial(multiply(a, b.a));
	}
	Polynomial operator*(Z k) const {
		auto c = *this;
		return c *= k;
	}

private:
	vector<Z> a;
};
