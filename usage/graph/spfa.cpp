// Standalone C++ file generated from graph/spfa.hpp
// Can be directly submitted to online judges

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;

inline constexpr ll inf = 0x3f3f3f3f3f3f3f3f;
inline constexpr int maxn = 100005, infint = 0x3f3f3f3f;
inline constexpr ld eps = 1e-9l, infld = 1e12l;

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

// === graph/spfa.hpp ===

// 返回空vector说明有负环
vector<ll> spfa(const vector<vector<pair<int, ll>>> &graph, int start) {
	int n = graph.size();
	vector<ll> dist(n, inf);
	vector<int> cnt(n, 0);
	vector<bool> inq(n, false);
	queue<int> q;
	q.push(start);
	dist[start] = 0;
	inq[start] = true;
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		inq[u] = false;
		for(auto [v, w] : graph[u]) {
			if(chkmin(dist[v], dist[u] + w)) {
				if(!inq[v]) {
					inq[v] = true;
					q.push(v);
					cnt[v] = cnt[u] + 1;
					if(cnt[v] > n) return {};
				}
			}
		}
	}
	return dist;
}

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
