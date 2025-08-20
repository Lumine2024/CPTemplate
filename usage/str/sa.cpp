// Standalone C++ file generated from str/sa.hpp
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

// === str/sa.hpp ===

vector<int> suffix_array(const string &str) {
	int n = str.size(), m = 128, p = 0;
	vector<int> rk(n * 3, -1), sa(n), id(n), cnt(max(n, m), 0);
	for(int i = 0; i < n; ++i) {
		rk[i] = str[i];
		cnt[rk[i]]++;
	}
	for(int i = 1; i < m; ++i) {
		cnt[i] += cnt[i - 1];
	}
	for(int i = n - 1; i >= 0; --i) {
		cnt[rk[i]]--;
		sa[cnt[rk[i]]] = i;
	}
	for(int w = 1;; w <<= 1, m = p + 1) {
		int cur = 0;
		for(int i = n - w; i < n; ++i) {
			id[cur] = i;
			++cur;
		}
		for(int i = 0; i < n; ++i) {
			if(sa[i] >= w) {
				id[cur] = sa[i] - w;
				++cur;
			}
		}
		cnt.assign(max(n, m), 0);
		for(int i = 0; i < n; ++i) {
			cnt[rk[i]]++;
		}
		for(int i = 1; i < m; ++i) {
			cnt[i] += cnt[i - 1];
		}
		for(int i = n - 1; i >= 0; --i) {
			cnt[rk[id[i]]]--;
			sa[cnt[rk[id[i]]]] = id[i];
		}
		p = 0;
		vector<int> oldrk = rk;
		rk[sa[0]] = 0;
		for(int i = 1; i < n; ++i) {
			if(oldrk[sa[i]] != oldrk[sa[i - 1]] || oldrk[sa[i] + w] != oldrk[sa[i - 1] + w]) {
				++p;
			}
			rk[sa[i]] = p;
		}
		if(p == n - 1) {
			break;
		}
	}
	return sa;
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
