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

string minrep(const string &str) {
	int n = str.size(), i = 0, j = 1, k = 0;
	string s = str + str;
	while(i < n && j < n) {
		while(k < n && s[i + k] == s[j + k]) ++k;
		if(k == n) break;
		if(s[i + k] > s[j + k]) i += (k + 1);
		else j += (k + 1);
		if(i == j) ++j;
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
