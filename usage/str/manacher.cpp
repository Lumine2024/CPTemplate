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

vector<int> manacher(const string &_s) {
	string s = "$";
	for(char ch : _s) {
		s += ch;
		s += '$';
	}
	int n = s.size();
	int mr = 0;
	int c = 0;
	vector<int> dp(n, 0);
	auto expand = [&](int l, int r) {
		while(l >= 0 && r < n && s[l] == s[r]) {
			--l;
			++r;
		}
		return (r - l) / 2;
	};
	for(int i = 0; i < n; ++i) {
		int m = 2 * c - i;
		if(i >= mr) {
			dp[i] = expand(i, i);
			mr = i + dp[i];
			c = i;
		} else if(dp[m] == mr - i) {
			dp[i] = expand(i - dp[m], i + dp[m]);
			mr = i + dp[i];
			c = i;
		} else {
			dp[i] = min(dp[m], mr - i);
		}
	}
	return dp;
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
