// Standalone C++ file generated from str/trie.hpp
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

// === str/trie.hpp ===

struct Trie {
	Trie() : nodes(1) {}
	void insert(const string &str) {
		int rt = 0;
		for(int i = 0; i < str.size(); ++i) {
			if((nodes[rt].nxt[getnum(str[i])]) == -1) {
				nodes[rt].nxt[getnum(str[i])] = nodes.size();
				nodes.emplace_back();
			}
			nodes[rt].cnt++;
			rt = nodes[rt].nxt[getnum(str[i])];
		}
		nodes[rt].cnt++;
		nodes[rt].end = true;
	}
	bool find(const string &str) const {
		int rt = 0;
		for(int i = 0; i < str.size(); ++i) {
			if((nodes[rt].nxt[getnum(str[i])]) == -1) {
				return false;
			}
			rt = nodes[rt].nxt[getnum(str[i])];
		}
		return nodes[rt].end;
	}
	int find_prefix(const string &str) const {
		int rt = 0;
		for(int i = 0; i < str.size(); ++i) {
			if((nodes[rt].nxt[getnum(str[i])]) == -1) {
				return 0;
			}
			rt = nodes[rt].nxt[getnum(str[i])];
		}
		return nodes[rt].cnt;
	}
private:
	struct Node {
		array<int, 65> nxt;
		bool end;
		int cnt;
		Node() : end(false), cnt(0) {
			nxt.fill(-1);
		}
	};
	vector<Node> nodes;
	static int getnum(char x) {
		if(x >= 'A' && x <= 'Z') {
			return x - 'A';
		} else if(x >= 'a' && x <= 'z') {
			return x - 'a' + 26;
		} else {
			return x - '0' + 52;
		}
	}
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
