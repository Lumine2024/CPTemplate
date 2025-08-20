
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;

inline constexpr ll modulo = 998244353, inf = 0x3f3f3f3f3f3f3f3f;

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


vector<vector<ll>> gauss(const vector<vector<ll>> &a, const vector<vector<ll>> &b) {
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
                    aug[i][j] = (aug[i][j] - f * aug[row][j] % modulo + modulo) % modulo;
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
                if(aug[i][n + j]) throw runtime_error("No solution");
            }
        }
    }
    for(int col = 0; col < n; ++col) {
        if(where[col] == -1) throw runtime_error("Multiple solutions");
    }
    vector<vector<ll>> ret(n, vector<ll>(m, 0));
    for(int col = 0; col < n; ++col) {
        for(int j = 0; j < m; ++j) {
            ret[col][j] = aug[where[col]][n + j];
        }
    }
    return ret;
}

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
