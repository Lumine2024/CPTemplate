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

template<class T> concept FenwickInfo = requires(T a, T b) {
	T{};
	{a + b} -> convertible_to<T>;
};
template<FenwickInfo T> struct Fenwick {
	explicit Fenwick(int n) : _nums(n + 1, 0), _n(n) {}
	T query(int x) const {
		T ans{};
		for(; x; x -= x & -x) ans = ans + _nums[x];
		return ans;
	}
	void update(int x, const T &v) {
		for(; x <= _n; x += x & -x) _nums[x] = _nums[x] + v;
	}
private:
	vector<T> _nums;
	int _n;
};
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
	Fenwick<ll> f1, f2;
};

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
