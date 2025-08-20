#pragma once
#include "constants.hpp"

struct Qread {
	Qread() : state(true) {}
	template<integral T> Qread &operator>>(T &val) {
		if(!state) {
			val = 0;
			return *this;
		}
		T x = 0, f = 1;
		char ch = cin.rdbuf()->sbumpc();
		while(ch < '0' || ch > '9') {
			if(ch == EOF) {
				state = false;
				cin.setstate(ios_base::eofbit);
				val = x * f;
				return *this;
			}
			if(ch == '-') {
				f = -1;
			}
			ch = cin.rdbuf()->sbumpc();
		}
		while(ch >= '0' && ch <= '9') {
			x = x * 10 + ch - '0';
			ch = cin.rdbuf()->sbumpc();
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