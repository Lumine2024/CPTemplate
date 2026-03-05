#include "../common.h"

constexpr ll modulo = 998244353;
inline ll qpow(ll x, ll n) {
	ll ret = 1;
	for(; n; n >>= 1, x = x * x % modulo)
		if(n & 1) ret = ret * x % modulo;
	return ret;
}

template<class T>
vector<vector<T>> matmul(const vector<vector<T>> &a,
						 const vector<vector<T>> &b) {
	int m = a.size(), n = a[0].size(), p = b[0].size();
	vector<vector<T>> ret(m, vector<T>(p, T(0)));
	for(int i = 0; i < m; ++i) {
		for(int j = 0; j < p; ++j) {
			for(int k = 0; k < n; ++k) {
				ret[i][j] = ret[i][j] + a[i][k] * b[k][j];
				// 增广矩乘：ret[i][j] = min(ret[i][j], lhs[i][k] + rhs[k][j]);
				// 对的对的，这就是floyd，对的对的
			}
		}
	}
	return ret;
}
template<class T> vector<vector<T>> matpow(vector<vector<T>> mat, ll n) {
	int M = mat.size();
	vector<vector<T>> ret(M, vector<T>(M, 0));
	for(int i = 0; i < M; ++i) {
		ret[i][i] = static_cast<T>(1);
	}
	for(; n != 0; n >>= 1, mat = matmul(mat, mat)) {
		if(n & 1ll) ret = matmul(ret, mat);
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
