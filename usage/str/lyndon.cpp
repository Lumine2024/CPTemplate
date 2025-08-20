
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


vector<string> duval(const string &s) {
    int n = s.size();
    vector<string> ret;
    for(int i = 0; i < n;) {
        int j = i + 1, k = i;
        while(j < n && s[k] <= s[j]) {
            (s[k] < s[j]) ? (k = i) : (k++);
            ++j;
        }
        while(i <= k) {
            ret.push_back(s.substr(i, j - k));
            i += (j - k);
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
