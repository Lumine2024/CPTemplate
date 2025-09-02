
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;

inline constexpr ll inf = 0x3f3f3f3f3f3f3f3f;

template<class T, class F> concept binary_func = convertible_to<F, function<bool(T, T)>>;
template<class T1, class T2, class F> requires(binary_func<T1, F> &&convertible_to<T2, T1>) bool chkf(T1 &x, const T2 &y, F &&f) {
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

vector<ll> dijkstra(vector<vector<pair<int, ll>>> &graph, int start) {
	int v = graph.size();
	vector<ll> dist(v, inf);
	dist[start] = 0;
	vector<bool> visited(v, false);
	priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
	for(auto [vtx, w] : graph[start]) {
		dist[vtx] = w;
		pq.emplace(w, vtx);
	}
	while(!pq.empty()) {
		auto [w, vtx] = pq.top();
		pq.pop();
		if(visited[vtx]) continue;
		visited[vtx] = true;
		for(auto [vt, ww] : graph[vtx]) {
			if(!visited[vt]) {
				if(chkmin(dist[vt], dist[vtx] + ww)) {
					pq.emplace(dist[vt], vt);
				}
			}
		}
	}
	return dist;
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
