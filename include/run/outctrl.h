#pragma once
#include "common.h"

template<class T>
concept CanOutput = requires(ostream os, T t) { os << t; };

class OutputController {
public:
	OutputController() {}
	template<CanOutput T>
	OutputController &operator<<(const T &t) {
		ss << t;
		return *this;
	}
	void flush() {
		cout << ss.str();
		ss.str("");
	}
	~OutputController() {
		flush();
	}
	template<CanOutput T>
	OutputController &force_output(const T &t) {
		cout << t;
		return *this;
	}
	streambuf *rdbuf() const {
		return cout.rdbuf();
	}
	streambuf *rdbuf(streambuf *buf) {
		return cout.rdbuf(buf);
	}
	ostream *tie(ostream *os) {
		return cout.tie(os);
	}
	ostream *tie() {
		return cout.tie();
	}

private:
	stringstream ss;
};

OutputController oc;
#define cout oc
