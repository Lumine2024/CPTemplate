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

struct ACAM {
	ACAM() : nodes(1) {}
	void insert(const string &str) {
		int rt = 0;
		for(int i = 0; i < (int)str.size(); ++i) {
			int id = str[i] - '0';
			if(nodes[rt].nxt[id] == -1) {
				nodes[rt].nxt[id] = nodes.size();
				nodes.emplace_back();
			}
			rt = nodes[rt].nxt[id];
		}
	}
	void build() {
		queue<int> q;
		nodes[0].fail = 0;
		for(int i = 0; i < 2; ++i) {
			int v = nodes[0].nxt[i];
			if(v != -1) {
				nodes[v].fail = 0;
				q.push(v);
			} else {
				nodes[0].nxt[i] = 0;
			}
		}
		while(!q.empty()) {
			int rt = q.front();
			q.pop();
			for(int i = 0; i < 2; ++i) {
				int v = nodes[rt].nxt[i];
				if(v != -1) {
					nodes[v].fail = nodes[nodes[rt].fail].nxt[i];
					q.push(v);
				} else {
					nodes[rt].nxt[i] = nodes[nodes[rt].fail].nxt[i];
				}
			}
		}
	}

private:
	struct Node {
		array<int, 2> nxt;
		int fail;
		Node() : fail(0) {
			nxt.fill(-1);
		}
	};
	vector<Node> nodes;
};

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
