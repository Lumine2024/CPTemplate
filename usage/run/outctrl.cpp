#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;

template<class T1, class T2, class F> bool chkf(T1 &x, const T2 &y, F &&f) {
	if(f(static_cast<T1>(y), x)) {
		x = static_cast<T1>(y);
		return true;
	}
	return false;
}
template<class T1, class T2> bool chkmin(T1 &x, const T2 &y) {
	return chkf(x, y, less<T1>{});
}
template<class T1, class T2> bool chkmax(T1 &x, const T2 &y) {
	return chkf(x, y, greater<T1>{});
}

template<class T>
concept CanOutput = requires(ostream os, T t) { os << t; };

template<class T> concept CanOutput = requires(ostream os, T t) {
	os << t;
};
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

inline void solve() {}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int n = 1;
	cin >> n;
	while(n--) {
		solve();
	}
	return 0;
}