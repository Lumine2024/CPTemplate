
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;

template<class T, class F> concept binary_func = convertible_to<F, function<bool(T, T)>>;
template<class T1, class T2, class F> requires(binary_func<T1, F> &&convertible_to<T2, T1>) bool chkf(T1 &x, const T2 &y, F &&f) {
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

struct Qread {
	Qread() : state(true) {
		cin.rdbuf()->pubsetbuf(buffer, maxn);
	}
	template<integral T> Qread &operator>>(T &val) {
		if(!state) {
			val = 0;
			return *this;
		}
		T x = 0, f = 1;
		char ch = cin.rdbuf()->sbumpc();
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
	static constexpr int maxn = 1 << 21;
	char buffer[maxn];
}qread;

inline void solve() {
	
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int t = 1;
	// cin >> t;
	while(t--) {
		solve();
	}
	return 0;
}
