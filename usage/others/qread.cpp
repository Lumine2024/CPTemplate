// Standalone C++ file generated from others/qread.hpp
// Can be directly submitted to online judges

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;

inline constexpr ll inf = 0x3f3f3f3f3f3f3f3f;
inline constexpr int maxn = 100005, infint = 0x3f3f3f3f;
inline constexpr ld eps = 1e-9l, infld = 1e12l;

template<class T, class F> bool chkf(T &x, const T &y, F &&f) {
    if(f(y, x)) {
        x = y;
        return true;
    }
    return false;
}
template<class T> bool chkmin(T &x, const T &y) {
    return chkf(x, y, less{});
}
template<class T> bool chkmax(T &x, const T &y) {
    return chkf(x, y, greater{});
}

// === others/qread.hpp ===

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

// Example usage:
inline void solve() {
    // Add your solution code here using the template above
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
