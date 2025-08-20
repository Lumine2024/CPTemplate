// Standalone C++ file generated from binary/lis.hpp
// Can be directly submitted to online judges

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;

inline constexpr ll modulo = 998244353, g = 3, inf = 0x3f3f3f3f3f3f3f3f;
inline constexpr int maxn = 100005, infint = 0x3f3f3f3f;
inline constexpr ld eps = 1e-9l, pi = 3.14159265358979323846264338327950288l, infld = 1e12l;

inline ll qpow(ll x, ll n) {
    ll ret = 1;
    for(; n != 0; n >>= 1, x = x * x % modulo) {
        if(n & 1) ret = ret * x % modulo;
    }
    return ret;
}

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

// === binary/lis.hpp ===

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
