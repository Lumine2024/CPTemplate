
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


struct BinaryLift {
	explicit BinaryLift(int n) : tree(n), anc(n, vector<int>(LOG, -1)), depth(n) {}
	void addedge(int u, int v) {
		tree[u].push_back(v);
		tree[v].push_back(u);
	}
	void build(int root) {
		dfs(root, -1);
	}
	int lca(int u, int v) const {
		if(depth[u] < depth[v]) swap(u, v);
		for(int k = LOG - 1; k >= 0; --k) {
			if(anc[u][k] != -1) {
				if(depth[anc[u][k]] >= depth[v]) {
					u = anc[u][k];
				}
			}
		}
		if(u == v) return u;
		for(int k = LOG - 1; k >= 0; --k) {
			if(anc[u][k] != anc[v][k]) {
				u = anc[u][k];
				v = anc[v][k];
			}
		}
		return anc[u][0];
	}
	int kth_ancestor(int x, int k) const {
		for(int i = 0; i < LOG; ++i) {
			if((k >> i) & 1) {
				x = anc[x][i];
				if(x == -1) return -1;
			}
		}
		return x;
	}
	vector<vector<int>> tree;
private:
	static constexpr int LOG = 20;
	vector<vector<int>> anc;
	vector<int> depth;
	void dfs(int root, int fa) {
		depth[root] = fa != -1 ? depth[fa] + 1 : 0;
		anc[root][0] = fa;
		for(int k = 1; k < LOG; ++k) {
			if(anc[root][k - 1] == -1) {
				anc[root][k] = -1;
			} else {
				anc[root][k] = anc[anc[root][k - 1]][k - 1];
			}
		}
		for(int v : tree[root]) {
			if(v != fa) {
				dfs(v, root);
			}
		}
	}
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
