// Standalone C++ file generated from graph/dinic.hpp
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

// === graph/dinic.hpp ===

struct Dinic {
	Dinic(int n, int s, int e)
		: graph(n), level(n), start(s), end(e), n(n) {}
	void addedge(int u, int v, ll w) {
		graph[u].emplace_back(Edge{ v, (int)graph[v].size(), w });
		graph[v].emplace_back(Edge{ u, (int)graph[u].size() - 1, 0 });
	}
	ll solve() {
		ll ans = 0;
		while(bfs()) {
			ll flow = dfs(start, inf);
			while(flow > 0) {
				ans += flow;
				flow = dfs(start, inf);
			}
		}
		return ans;
	}
private:
	struct Edge {
		int to;
		int rev;
		ll cap;
	};
	vector<vector<Edge>> graph;
	vector<int> level;
	int n;
	int start, end;
	bool bfs() {
		fill(level.begin(), level.end(), -1);
		level[start] = 0;
		queue<int> q;
		q.emplace(start);
		while(!q.empty()) {
			int u = q.front();
			q.pop();
			for(const auto &e : graph[u]) {
				if(level[e.to] == -1 && e.cap > 0) {
					level[e.to] = level[u] + 1;
					q.emplace(e.to);
				}
			}
		}
		return level[end] != -1;
	}
	ll dfs(int u, ll max_flow) {
		if(u == end || max_flow == 0) return max_flow;
		ll total_flow = 0;
		for(auto &e : graph[u]) {
			if(level[e.to] == level[u] + 1 && e.cap > 0) {
				ll min_flow = min(max_flow, e.cap);
				ll pushed = dfs(e.to, min_flow);
				if(pushed > 0) {
					e.cap -= pushed;
					graph[e.to][e.rev].cap += pushed;
					total_flow += pushed;
					max_flow -= pushed;
					if(max_flow == 0) {
						return total_flow;
					}
				}
			}
		}
		return total_flow;
	}
};

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
