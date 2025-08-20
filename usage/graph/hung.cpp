
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


int hungarian(const vector<vector<int>> &graph, int vsz) {
	int usz = graph.size();
	vector<int> mu(usz, -1);
	vector<int> mv(vsz, -1);
	auto dfs = [&](auto &&dfs, int u, vector<bool> &visited) -> bool {
		for(int v : graph[u]) {
			if(visited[v]) continue;
			visited[v] = true;
			if(mv[v] == -1 || dfs(dfs, mv[v], visited)) {
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
			vector<bool> visited(vsz, false);
			if(dfs(dfs, u, visited)) {
				ret++;
			}
		}
	}
	return ret;
}

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
