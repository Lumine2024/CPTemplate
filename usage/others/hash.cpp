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

struct MyHash {
	size_t operator()(ll _x) const noexcept {
		ull x = _x;
		x ^= c;
		x ^= (x >> 21);
		x ^= (x << 37);
		x ^= (x >> 4);
		x *= 0x27d4eb2f165667c5;
		x *= c;
		x ^= (x >> 28);
		x *= 0x165667b19e3779f9;
		x ^= (x >> 31);
		return x ^ c;
	}

private:
	static inline const size_t c =
		(size_t)chrono::steady_clock::now().time_since_epoch().count();
};

inline void solve() {}

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
