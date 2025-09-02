
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
