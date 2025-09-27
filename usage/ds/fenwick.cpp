
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
template<class T> concept RangeFenwickInfo = requires(T a, T b, int c) {
	{a - b} -> convertible_to<T>;
	{a * c} -> convertible_to<T>;
	{-a} -> convertible_to<T>;
} && FenwickInfo<T>;
template<RangeFenwickInfo T> struct RangeFenwick {
	explicit RangeFenwick(int n) : _f1(n), _f2(n), _n(n) {}
	void update(int l, int r, const T &v) {
		_update(l, v);
		_update(r, -v);
	}
	T query(int x) const {
		return x * _f1.query(x) - _f2.query(x);
	}
private:
	Fenwick<T> _f1, _f2;
	int _n;
	void _update(int x, const T &v) {
		_f1.update(x, v);
		_f2.update(x, v * (x - 1));
	}
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
