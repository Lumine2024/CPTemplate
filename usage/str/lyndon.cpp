#include "../common.h"

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
