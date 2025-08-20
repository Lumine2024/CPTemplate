// Standalone C++ file generated from str/seqam.hpp
// Can be directly submitted to online judges

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;

inline constexpr ll inf = 0x3f3f3f3f3f3f3f3f;
inline constexpr int maxn = 100005, infint = 0x3f3f3f3f;
inline constexpr ld eps = 1e-9l, infld = 1e12l;

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

// === str/seqam.hpp ===

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
