// Standalone C++ file generated from ds/sparse.hpp
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

// === ds/sparse.hpp ===

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
