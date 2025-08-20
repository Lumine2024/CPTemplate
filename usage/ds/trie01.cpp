// Standalone C++ file generated from ds/trie01.hpp
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

// === ds/trie01.hpp ===

struct Trie01 {
	Trie01() : nodes(1) {}
	void insert(ll val) {
		int now = 0;
		for(ll i = 62; i >= 0; --i) {
			ll flag = (val >> i) & 1;
			if(nodes[now].nxt[flag] == -1) {
				nodes[now].nxt[flag] = nodes.size();
				nodes.emplace_back();
			}
			now = nodes[now].nxt[flag];
		}
	}
	ll qmax_xor(ll val) const {
		int now = 0;
		ll ans = 0;
		for(ll i = 62; i >= 0; --i) {
			ll flag = (val >> i) & 1;
			if(nodes[now].nxt[1 ^ flag] != -1) {
				ans += (1ll << i);
				now = nodes[now].nxt[1 ^ flag];
			} else {
				now = nodes[now].nxt[flag];
			}
		}
		return ans;
	}
private:
	static constexpr int height = 63;
	struct Node {
		int nxt[2];
		Node() {
			nxt[0] = nxt[1] = -1;
		}
	};
	vector<Node> nodes;
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
