#include "common.h"

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
