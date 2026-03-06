#include "common.h"

// persistent segment tree
struct PST {
	explicit PST(int n_) : n(n_) {
		nodes.reserve(2 * n * (int)log2(n));
		vers.reserve(n + 1);
		vers.push_back(_build(0, n - 1));
	}
	void update(int k) {
		vers.push_back(_update(k, vers.back(), 0, n - 1));
	}
	// 这里为解决静态区间第k小问题设计，传入k, l, r
	int query(int k, int ver1, int ver2) const {
		return _query(k, vers[ver1 - 1], vers[ver2], 0, n - 1);
	}

private:
	struct Node {
		int l, r;
		int cnt;
	};
	vector<Node> nodes;
	vector<int> vers;
	int n;
	int _build(int l, int r) {
		int ret = nodes.size();
		if(l == r) {
			nodes.emplace_back(-1, -1, 0);
			return ret;
		}
		nodes.emplace_back(-1, -1, 0);
		int mid = (l + r) / 2;
		nodes[ret].l = _build(l, mid);
		nodes[ret].r = _build(mid + 1, r);
		return ret;
	}
	int _update(int k, int root, int l, int r) {
		int ret = nodes.size();
		nodes.emplace_back(nodes[root]);
		nodes[ret].cnt++;
		if(l == r) return ret;
		int mid = (l + r) / 2;
		if(k <= mid) nodes[ret].l = _update(k, nodes[root].l, l, mid);
		else nodes[ret].r = _update(k, nodes[root].r, mid + 1, r);
		return ret;
	}
	int _query(int k, int root1, int root2, int l, int r) const {
		if(l == r) return l;
		int mid = (l + r) / 2;
		int cntl = nodes[nodes[root2].l].cnt - nodes[nodes[root1].l].cnt;
		if(k <= cntl) return _query(k, nodes[root1].l, nodes[root2].l, l, mid);
		else
			return _query(k - cntl, nodes[root1].r, nodes[root2].r, mid + 1, r);
	}
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
