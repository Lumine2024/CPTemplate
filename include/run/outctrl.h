#pragma once
#include "common.h"

template<class T>
concept CanOutput = requires(ostream os, T t) { os << t; };

class OutputController {
public:
	OutputController() {}
	template<CanOutput T> OutputController &operator<<(const T &t) {
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
	template<CanOutput T> void force_output(const T &t) {
		cout << t;
	}

private:
	stringstream ss;
};

OutputController oc;
#define cout oc
