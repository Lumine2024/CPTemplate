#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

struct Qread {
	Qread() : state(true) {}
	template<integral T> Qread &operator>>(T &val) {
		if(!state) {
			val = 0;
			return *this;
		}
		T x = 0, f = 1;
		char ch = getchar();
		while(ch < '0' || ch > '9') {
			if(ch == EOF) {
				state = false;
				val = 0;
				return *this;
			}
			if(ch == '-') {
				f = -1;
			}
			ch = getchar();
		}
		while(ch >= '0' && ch <= '9') {
			x = x * 10 + ch - '0';
			ch = getchar();
		}
		val = x * f;
		return *this;
	}
	explicit operator bool() const {
		return state;
	}
private:
	bool state;
};
Qread qread;