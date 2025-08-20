
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;


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


struct PAM {
	PAM() : s("#"), last(1) {
		nodes.emplace_back(-1, 0);
		nodes.emplace_back(0, 0);
	}
	int insert(char ch) {
		s += ch;
		int pos = s.size() - 1;
		int p = last, id = ch - 'a';
		while(s[pos - nodes[p].len - 1] != ch) {
			p = nodes[p].fail;
		}
		if(nodes[p].nxt[id] == -1) {
			int cur = nodes.size();
			nodes[p].nxt[id] = cur;
			nodes.emplace_back(nodes[p].len + 2, 0);
			if(nodes[cur].len == 1) {
				nodes[cur].fail = 1;
			} else {
				int f = nodes[p].fail;
				while(s[pos - nodes[f].len - 1] != ch) {
					f = nodes[f].fail;
				}
				nodes[cur].fail = nodes[f].nxt[id];
			}
			if(nodes[cur].len == 1) {
				nodes[cur].cnt = 1;
			} else {
				nodes[cur].cnt = nodes[nodes[cur].fail].cnt + 1;
			}
		}
		last = nodes[p].nxt[id];
		return nodes[last].cnt;
	}
private:
	struct Node {
		int len, fail, cnt;
		array<int, 26> nxt;
		Node(int l, int f) : len(l), fail(f), cnt(0) {
			nxt.fill(-1);
		}
	};
	vector<Node> nodes;
	string s;
	int last;
};

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
