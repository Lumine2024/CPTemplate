// Standalone C++ file generated from str/minrep.hpp
// Can be directly submitted to online judges

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;

inline constexpr ll inf = 0x3f3f3f3f3f3f3f3f;
inline constexpr int maxn = 100005, infint = 0x3f3f3f3f;
inline constexpr ld eps = 1e-9l, infld = 1e12l;

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

// === str/minrep.hpp ===

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
