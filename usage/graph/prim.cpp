// Standalone C++ file generated from graph/prim.hpp
// Can be directly submitted to online judges

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;

inline constexpr ll modulo = 998244353, g = 3, inf = 0x3f3f3f3f3f3f3f3f;
inline constexpr int maxn = 100005, infint = 0x3f3f3f3f;
inline constexpr ld eps = 1e-9l, pi = 3.14159265358979323846264338327950288l, infld = 1e12l;

inline ll qpow(ll x, ll n) {
    ll ret = 1;
    for(; n != 0; n >>= 1, x = x * x % modulo) {
        if(n & 1) ret = ret * x % modulo;
    }
    return ret;
}

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

// === graph/prim.hpp ===

ll prim(const vector<vector<pair<int, ll>>> &graph) {
	int n = graph.size();
	vector<bool> visited(n, false);
	vector<ll> dist(n, inf);
	dist[0] = 0;
	priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
	pq.emplace(0, 0);
	ll ret = 0;
	while(!pq.empty()) {
		auto [w, v] = pq.top();
		pq.pop();
		if(visited[v]) continue;
		visited[v] = true;
		ret += w;
		for(auto [u, w] : graph[v]) {
			if(!visited[u] && dist[u] > w) {
				dist[u] = w;
				pq.emplace(w, u);
			}
		}
	}
	for(bool b : visited) {
		if(!b) {
			return inf;
		}
	}
	return ret;
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
