#include "common.h"

vector<int> lis(const vector<int> &nums) {
	int n = nums.size();
	vector<int> dp, pos(n), pre(n, -1);
	for(int i = 0; i < n; ++i) {
		auto it = lower_bound(dp.begin(), dp.end(), nums[i]);
		if(it == dp.end()) dp.push_back(nums[i]);
		else *it = nums[i];
		int j = it - dp.begin();
		pos[j] = i;
		if(j != 0) pre[i] = pos[j - 1];
	}
	vector<int> ret;
	for(int i = pos[dp.size() - 1]; i != -1; i = pre[i]) {
		ret.push_back(nums[i]);
	}
	reverse(ret.begin(), ret.end());
	return ret;
}

inline void solve() {}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int t = 1;
	// cin >> t;
	for(int i = 0; i < t; ++i) {
		solve();
	}
	return 0;
}
