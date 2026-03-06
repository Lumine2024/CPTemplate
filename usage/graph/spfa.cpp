#include "common.h"

constexpr ll inf = 0x3f3f3f3f3f3f3f3f;

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
			if(dist[v] > dist[u] + w) {
				dist[v] = dist[u] + w;
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
