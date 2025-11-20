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

int hungarian(const vector<vector<int>> &graph, int vsz) {
	int usz = graph.size();
	vector<int> mu(usz, -1);
	vector<int> mv(vsz, -1);
	auto dfs = [&](auto &&dfs, int u, vector<bool> &vis) -> bool {
		for(int v : graph[u]) {
			if(vis[v]) continue;
			vis[v] = true;
			if(mv[v] == -1 || dfs(dfs, mv[v], vis)) {
				mv[v] = u;
				mu[u] = v;
				return true;
			}
		}
		return false;
	};
	int ret = 0;
	for(int u = 0; u < usz; ++u) {
		if(mu[u] == -1) {
			vector<bool> vis(vsz, false);
			if(dfs(dfs, u, vis)) ret++;
		}
	}
	return ret;
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
