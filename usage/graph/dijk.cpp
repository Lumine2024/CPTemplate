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

inline constexpr ll inf = 0x3f3f3f3f3f3f3f3f;

vector<ll> dijkstra(const vector<vector<pair<int, ll>>> &graph, int start) {
	int v = graph.size();
	vector<ll> dist(v, inf);
	dist[start] = 0;
	vector<bool> vis(v, false);
	priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
	for(auto [v, w] : graph[start]) {
		dist[v] = w;
		pq.emplace(w, v);
	}
	while(!pq.empty()) {
		auto [w, u] = pq.top();
		pq.pop();
		if(vis[u]) continue;
		vis[u] = true;
		for(auto [v, ww] : graph[u]) {
			if(!vis[v] && dist[v] > dist[u] + ww) {
				dist[v] = dist[u] + ww;
				pq.emplace(dist[v], v);
			}
		}
	}
	return dist;
}

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
