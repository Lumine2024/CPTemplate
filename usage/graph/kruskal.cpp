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

constexpr ll inf = 0x3f3f3f3f3f3f3f3f;

struct DSU {
	explicit DSU(int n) : fs(n, -1) {}
	int find(int x) {
		if(fs[x] < 0) return x;
		return fs[x] = find(fs[x]);
	}
	bool is_connected(int x, int y) {
		return find(x) == find(y);
	}
	int size(int x) {
		return -fs[find(x)];
	}
	void connect(int x, int y) {
		x = find(x); y = find(y);
		if(x == y) return;
		int sx = size(x), sy = size(y);
		if(sx < sy) {
			fs[y] -= sx;
			fs[x] = y;
		} else {
			fs[x] -= sy;
			fs[y] = x;
		}
	}
private:
	vector<int> fs; // fa or size
};

struct Edge {
	int u, v;
	ll w;
};

ll kruskal(vector<Edge> &edges, int n) {
	DSU dsu(n);
	ll ans = 0;
	sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) {
		return a.w < b.w;
	});
	for(auto &e : edges) {
		if(!dsu.is_connected(e.u, e.v)) {
			dsu.connect(e.u, e.v);
			ans += e.w;
		}
	}
	for(int i = 1; i < n; ++i) {
		if(!dsu.is_connected(i, 0)) return inf;
	}
	return ans;
}

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
