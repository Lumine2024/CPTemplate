#include "../common.h"

constexpr ll inf = 0x3f3f3f3f3f3f3f3f;

ll prim(const vector<vector<pair<int, ll>>> &graph) {
	int n = graph.size();
	vector<bool> vis(n, false);
	vector<ll> dist(n, inf);
	dist[0] = 0;
	priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
	pq.emplace(0, 0);
	ll ret = 0;
	while(!pq.empty()) {
		auto [w, v] = pq.top();
		pq.pop();
		if(vis[v]) continue;
		vis[v] = true;
		ret += w;
		for(auto [u, w] : graph[v]) {
			if(!vis[u] && dist[u] > w) {
				dist[u] = w;
				pq.emplace(w, u);
			}
		}
	}
	for(bool b : vis) {
		if(!b) return inf;
	}
	return ret;
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
