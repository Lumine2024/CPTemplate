// Standalone C++ file generated from ds/arithfen.hpp
// Can be directly submitted to online judges

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;

inline constexpr ll modulo = 998244353, g = 3, inf = 0x3f3f3f3f3f3f3f3f;
inline constexpr int maxn = 100005, infint = 0x3f3f3f3f;
inline constexpr ld eps = 1e-9l, pi = 3.14159265358979323846264338327950288l, infld = 1e12l;

inline ll qpow(ll x, ll n) {
    ll ret = 1;
    for(; n != 0; n >>= 1, x = x * x % modulo) {
        if(n & 1) ret = ret * x % modulo;
    }
    return ret;
}

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

// === ds/fenwick.hpp ===

// 单点
struct Fenwick {
	explicit Fenwick(int n) : n(n), nums(n + 1, 0) {}
	ll query(int x) const {
		ll ans = 0;
		for(; x; x -= lbit(x)) {
			ans += nums[x];
		}
		return ans;
	}
	void update(int x, ll v) {
		for(; x <= n; x += lbit(x)) {
			nums[x] += v;
		}
	}
private:
	vector<ll> nums;
	int n;
	static int lbit(int x) {
		return x & -x;
	}
};
// 区间
struct RangeFenwick {
	const int n;
	explicit RangeFenwick(int n)
		: n(n), f1(n), f2(n) {}
	void update(int l, int r, ll v) {
		_update(l, v);
		_update(r + 1, -v);
	}
	ll query(int l, int r) const {
		return _query(r) - _query(l - 1);
	}
private:
	Fenwick f1, f2;
	void _update(int x, ll v) {
		f1.update(x, v);
		f2.update(x, v * (x - 1));
	}
	ll _query(int x) const {
		return f1.query(x) * x - f2.query(x);
	}
};

// === ds/arithfen.hpp ===

struct ArithmeticFenwick {
	explicit ArithmeticFenwick(int n)
		: f1(n + 2), f2(n + 2) {}
	// a*idx+b
	void update(int l, int r, ll a, ll b) {
		f1.update(l, b);
		f1.update(r + 1, -b - a * (r - l + 1));
		f2.update(l, a);
		f2.update(r + 1, -a);
	}
	ll query(ll idx) const {
		return f1.query(idx) + idx * f2.query(idx);
	}
private:
	Fenwick f1, f2;
};

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
