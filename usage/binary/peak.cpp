
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
