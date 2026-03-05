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

// 得到用于KMP的数组
vector<int> kmp_f(const string &s) {
	int n = s.size();
	vector<int> f(n, 0);
	for(int i = 1, j = 0; i < n; ++i) {
		while(j > 0 && s[i] != s[j]) j = f[j - 1];
		if(s[i] == s[j]) ++j;
		f[i] = j;
	}
	return f;
}
// 寻找第一次在off后面haystack中的needle
int kmp_find(const string &haystack, const string &needle, int off = 0) {
	int n = needle.size(), m = haystack.size();
	vector<int> f = kmp_f(needle);
	for(int i = 0, j = off; j < m;) {
		if(haystack[j] == needle[i]) {
			++i;
			++j;
			if(i == n) return j - n;
		} else {
			(i == 0) ? (++j) : (i = f[i - 1]);
		}
	}
	return -1;
}
// 返回haystack中有多少个needle，可重（即10101有两个101）
int kmp_count(const string &haystack, const string &needle) {
	int n = needle.size(), m = haystack.size();
	int ret = 0;
	vector<int> f = kmp_f(needle);
	for(int i = 0, j = 0; j < m;) {
		if(haystack[j] == needle[i]) {
			++i;
			++j;
			if(i == n) {
				++ret;
				i = f[i - 1];
			}
		} else {
			(i == 0) ? (++j) : (i = f[i - 1]);
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
