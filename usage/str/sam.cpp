// Standalone C++ file generated from str/sam.hpp
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

// === str/sam.hpp ===

struct SAM {
	SAM() : nodes(1, Node(-1, 0)), last(0) {}
	void insert(char ch) {
		const int id = ch - 'a';
		const int cur = nodes.size();
		nodes.emplace_back(-1, nodes[last].len + 1);
		int p = last;
		while(p != -1 && nodes[p].nxt[id] == -1) {
			nodes[p].nxt[id] = cur;
			p = nodes[p].link;
		}
		if(p == -1) {
			nodes[cur].link = 0;
		} else {
			int q = nodes[p].nxt[id];
			if(nodes[p].len + 1 == nodes[q].len) {
				nodes[cur].link = q;
			} else {
				int clone = nodes.size();
				nodes.emplace_back(nodes[q].link, nodes[p].len + 1);
				nodes[clone].nxt = nodes[q].nxt;
				while(p != -1 && nodes[p].nxt[id] == q) {
					nodes[p].nxt[id] = clone;
					p = nodes[p].link;
				}
				nodes[q].link = nodes[cur].link = clone;
			}
		}
		last = cur;
		ends.push_back(cur);
	}
	ll solve() const {
		int n = nodes.size();
		vector<int> indeg(n, 0), topoorder;
		topoorder.reserve(n);
		for(int i = 0; i < n; ++i) {
			if(nodes[i].link != -1) {
				indeg[nodes[i].link]++;
			}
		}
		queue<int> q;
		for(int i = 0; i < n; ++i) {
			if(indeg[i] == 0) {
				q.push(i);
			}
		}
		while(!q.empty()) {
			int u = q.front();
			q.pop();
			topoorder.push_back(u);
			if(nodes[u].link != -1) {
				indeg[nodes[u].link]--;
				if(indeg[nodes[u].link] == 0) {
					q.push(nodes[u].link);
				}
			}
		}
		ll ans = 0;
		vector<ll> occur(n, 0);
		for(int e : ends) {
			occur[e] = 1;
		}
		for(int i : topoorder) {
			if(nodes[i].link != -1) {
				occur[nodes[i].link] += occur[i];
			}
			if(occur[i] != 1) {
				ans = max(ans, occur[i] * nodes[i].len);
			}
		}
		return ans;
	}
private:
	struct Node {
		array<int, 26> nxt;
		int link;
		int len;
		Node(int lk, int ln) : link(lk), len(ln) {
			nxt.fill(-1);
		}
	};
	vector<Node> nodes;
	vector<int> ends;
	int last;
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
