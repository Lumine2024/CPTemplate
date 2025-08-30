#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;

template<class T, class F> concept binary_func = convertible_to<F, function<bool(T, T)>>;
template<class T1, class T2, class F> requires(binary_func<T1, F> &&convertible_to<T2, T1>) bool chkf(T1 &x, const T2 &y, F &&f) {
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

inline void solve() {
    
}

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
