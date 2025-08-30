
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

string manacher(const string &_s) {
	string s = "$";
	for(char ch : _s) {
		s += ch;
		s += '$';
	}
	int n = s.size();
	int max_right = 0;
	int center = 0;
	vector<int> dp(n, 0);
	auto expand = [&](int left, int right) {
		while(left >= 0 && right < n && s[left] == s[right]) {
			--left;
			++right;
		}
		return (right - left) / 2;
	};
	for(int i = 0; i < n; ++i) {
		int mirror = 2 * center - i;
		if(i >= max_right) {
			dp[i] = expand(i, i);
			max_right = i + dp[i];
			center = i;
		} else if(dp[mirror] == max_right - i) {
			dp[i] = expand(i - dp[mirror], i + dp[mirror]);
			max_right = i + dp[i];
			center = i;
		} else {
			dp[i] = min(dp[mirror], max_right - i);
		}
	}
	auto it = max_element(dp.begin(), dp.end());
	int id = it - dp.begin(), len = *it;
	string ret;
	for(int i = id - len + 1; i < id + len; ++i) {
		if(s[i] != '$') {
			ret += s[i];
		}
	}
	return ret;
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
