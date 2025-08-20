
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;


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


template<class T> vector<vector<T>> matmul(const vector<vector<T>> &lhs, const vector<vector<T>> &rhs) {
	int M = lhs.size(), N = lhs[0].size(), P = rhs[0].size();
	vector<vector<T>> ret(M, vector<T>(P, 0));
	for(int i = 0; i < M; ++i) {
		for(int j = 0; j < P; ++j) {
			for(int k = 0; k < N; ++k) {
				ret[i][j] = ret[i][j] + lhs[i][k] * rhs[k][j];
				// 增广矩乘：ret[i][j] = min(ret[i][j], lhs[i][k] + rhs[k][j]);
				// 对的对的，这就是floyd，对的对的
			}
		}
	}
	return ret;
}
template<class T> vector<vector<T>> matpow(vector<vector<T>> mat, ll N) {
	int M = mat.size();
	vector<vector<T>> ret(M, vector<T>(M, 0));
	for(int i = 0; i < M; ++i) {
		ret[i][i] = static_cast<T>(1);
	}
	for(; N != 0; N >>= 1, mat = matmul(mat, mat)) {
		if(N & 1ll) {
			ret = matmul(ret, mat);
		}
	}
	return ret;
}

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
