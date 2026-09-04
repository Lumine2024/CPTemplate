#pragma once
#include "common.h"

struct Qread {
	Qread() : state(true) {
		cin.rdbuf()->pubsetbuf(buffer, maxn);
	}
	int getc() {
		return cin.rdbuf()->sbumpc();
	}
	template<integral T>
	Qread &operator>>(T &val) {
		if(!state) {
			val = 0;
			return *this;
		}
		T x = 0, f = 1;
		char ch = getc();
		while(ch < '0' || ch > '9') {
			if(ch == char_traits<char>::eof()) {
				state = false;
				cin.setstate(ios_base::eofbit);
				val = x * f;
				return *this;
			}
			if(ch == '-') {
				f = -1;
			}
			ch = getc();
		}
		while(ch >= '0' && ch <= '9') {
			x = x * 10 + ch - '0';
			ch = getc();
		}
		val = x * f;
		return *this;
	}
	Qread &operator>>(string &val) {
		val.clear();
		if(!state) {
			return *this;
		}
		int ch = getc();
		while(ch != char_traits<char>::eof() && isspace(ch)) {
			ch = getc();
		}
		if(ch == char_traits<char>::eof()) {
			state = false;
			cin.setstate(ios_base::eofbit);
			return *this;
		}
		while(ch != char_traits<char>::eof() && !isspace(ch)) {
			val.push_back(char(ch));
			ch = getc();
		}
		return *this;
	}
	explicit operator bool() const {
		return state;
	}

private:
	bool state;
	static constexpr int maxn = 1 << 21;
	char buffer[maxn];
} qread;
