
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

vector<int> suffix_array(const string &str) {
	int n = str.size(), m = 128, p = 0;
	vector<int> rk(n * 3, -1), sa(n), id(n), cnt(max(n, m), 0);
	for(int i = 0; i < n; ++i) cnt[rk[i] = str[i]]++;
	for(int i = 1; i < m; ++i) cnt[i] += cnt[i - 1];
	for(int i = n - 1; i >= 0; --i) sa[--cnt[rk[i]]] = i;
	for(int w = 1; ; w <<= 1, m = p + 1) {
		int cur = 0;
		for(int i = n - w; i < n; ++i) id[cur++] = i;
		for(int i = 0; i < n; ++i) {
			if(sa[i] >= w) id[cur++] = sa[i] - w;
		}
		cnt.assign(max(n, m), 0);
		for(int i = 0; i < n; ++i) cnt[rk[i]]++;
		for(int i = 1; i < m; ++i) cnt[i] += cnt[i - 1];
		for(int i = n - 1; i >= 0; --i) sa[--cnt[rk[id[i]]]] = id[i];
		p = 0;
		vector<int> oldrk = rk;
		rk[sa[0]] = 0;
		for(int i = 1; i < n; ++i) {
			if(oldrk[sa[i]] != oldrk[sa[i - 1]] ||
				oldrk[sa[i] + w] != oldrk[sa[i - 1] + w]) ++p;
			rk[sa[i]] = p;
		}
		if(p == n - 1) break;
	}
	return sa;
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
