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

template<class T> struct Sparse {
	using func_type = function<T(T, T)>;
	Sparse(const vector<T> &vec, func_type fn) : func(fn) {
		int n = vec.size();
		_log.resize(n + 1);
		_log[0] = -1;
		for(int i = 1; i <= n; ++i) {
			_log[i] = _log[i >> 1] + 1;
		}
		int k = _log[n] + 1;
		table.resize(n, vector<T>(k));
		for(int i = 0; i < n; ++i) {
			table[i][0] = vec[i];
		}
		for(int j = 1; j < k; ++j) {
			int step = 1 << (j - 1);
			for(int i = 0; i + step < n; ++i) {
				table[i][j] = func(table[i][j - 1], table[i + step][j - 1]);
			}
		}
	}
	T query(int l, int r) const {
		int len = r - l + 1;
		int j = _log[len];
		return func(table[l][j], table[r - (1 << j) + 1][j]);
	}

private:
	vector<vector<T>> table;
	vector<int> _log;
	func_type func;
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
