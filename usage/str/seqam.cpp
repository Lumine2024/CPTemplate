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

struct SeqAM {
	explicit SeqAM(const string &s) : n(s.size()), nxt(s.size() + 2, [&] {
		array<int, 26> ret;
		ret.fill(s.size() + 1);
		return ret;
	}()) {
		for(int i = n - 1; i >= 0; --i) {
			nxt[i] = nxt[i + 1];
			nxt[i][s[i] - 'a'] = i + 1;
		}
	}
	bool match(const string &t) const {
		int now = 0;
		for(char c : t) {
			now = nxt[now][c - 'a'];
		}
		return now != (n + 1);
	}
private:
	int n;
	vector<array<int, 26>> nxt;
};

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
