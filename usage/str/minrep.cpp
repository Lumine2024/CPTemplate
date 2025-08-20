
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


string minstr(const string &str) {
	int n = str.size(), i = 0, j = 1, k = 0;
	string s = str + str;
	while(i < n && j < n) {
		while(k < n && s[i + k] == s[j + k]) {
			++k;
		}
		if(k == n)
			break;
		if(s[i + k] > s[j + k]) {
			i += (k + 1);
		} else {
			j += (k + 1);
		}
		if(i == j) {
			++j;
		}
		k = 0;
	}
	return s.substr(min(i, j), n);
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
