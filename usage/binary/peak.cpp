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

int peak(const vector<int> &nums) {
	int n = nums.size();
	int l = 0, r = n - 1;
	int ll = (r - l) / 3, rr = (r - l) * 2 / 3;
	while(l < r) {
		if(nums[ll] < nums[rr]) {
			l = ll + 1;
		} else {
			r = rr;
		}
		ll = l + (r - l) / 3;
		rr = l + (r - l) * 2 / 3;
	}
	return l;
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
