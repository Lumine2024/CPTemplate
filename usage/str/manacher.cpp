#include "common.h"

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
