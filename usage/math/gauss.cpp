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

constexpr ll modulo = 998244353;
inline ll qpow(ll x, ll n) {
	ll ret = 1;
	for(; n; n >>= 1, x = x * x % modulo)
		if(n & 1) ret = ret * x % modulo;
	return ret;
}

optional<vector<vector<ll>>> gauss(const vector<vector<ll>> &a,
								   const vector<vector<ll>> &b) {
	int r = a.size(), n = a[0].size(), m = b[0].size(), row = 0;
	vector<vector<ll>> aug(r, vector<ll>(n + m));
	for(int i = 0; i < r; ++i) {
		for(int j = 0; j < m + n; ++j) {
			aug[i][j] = (j < n) ? a[i][j] : b[i][j - n];
		}
	}
	vector<int> where(n, -1);
	for(int col = 0; col < n && row < r; ++col) {
		int sel = row;
		while(sel < r && aug[sel][col] == 0) ++sel;
		if(sel == r) continue;
		swap(aug[row], aug[sel]);
		ll inv = qpow(aug[row][col], modulo - 2);
		for(int j = col; j < n + m; ++j) {
			aug[row][j] = aug[row][j] * inv % modulo;
		}
		for(int i = 0; i < r; ++i) {
			if(i != row && aug[i][col]) {
				ll f = aug[i][col];
				for(int j = col; j < n + m; ++j) {
					aug[i][j] =
						(aug[i][j] - f * aug[row][j] % modulo + modulo) %
						modulo;
				}
			}
		}
		where[col] = row;
		++row;
	}
	for(int i = row; i < r; ++i) {
		bool flag = true;
		for(int j = 0; j < n; ++j) {
			if(aug[i][j] != 0) {
				flag = false;
				break;
			}
		}
		if(flag) {
			for(int j = 0; j < m; ++j) {
				if(aug[i][n + j]) return nullopt;
			}
		}
	}
	for(int col = 0; col < n; ++col) {
		if(where[col] == -1) return nullopt;
	}
	vector<vector<ll>> ret(n, vector<ll>(m, 0));
	for(int col = 0; col < n; ++col) {
		for(int j = 0; j < m; ++j) {
			ret[col][j] = aug[where[col]][n + j];
		}
	}
	return ret;
}

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
