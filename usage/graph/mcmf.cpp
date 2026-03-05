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

constexpr ll inf = 0x3f3f3f3f3f3f3f3f;

struct EK {
	struct Edge {
		int dst, rev;
		ll weight, flow;
		bool neg;
	};
	vector<vector<Edge>> graph;
	int n;
	explicit EK(int _n) : n(_n), graph(_n) {}
	void addedge(int u, int v, ll flow, ll weight) {
		int iu = graph[u].size(), iv = graph[v].size();
		graph[u].push_back({v, iv, weight, flow, false});
		graph[v].push_back({u, iu, -weight, 0, true});
	}
	pair<ll, ll> mcmf(int s, int t) {
		ll cost = 0, flow = 0;
		while(true) {
			vector<int> pv(n, -1), pe(n, -1);
			vector<ll> d(n, inf), mf(n, 0);
			vector<bool> inq(n, false);
			queue<int> q;
			q.push(s);
			d[s] = 0;
			mf[s] = inf;
			inq[s] = true;
			while(!q.empty()) {
				int u = q.front();
				q.pop();
				inq[u] = false;
				for(int i = 0; i < graph[u].size(); ++i) {
					auto &e = graph[u][i];
					int v = e.dst;
					ll f = e.flow, w = e.weight;
					if(f > 0 && d[u] + w < d[v]) {
						d[v] = d[u] + w;
						pv[v] = u;
						pe[v] = i;
						mf[v] = min(mf[u], f);
						if(!inq[v]) {
							q.push(v);
							inq[v] = true;
						}
					}
				}
			}
			if(mf[t] <= 0) break;
			ll add = mf[t];
			for(int v = t; v != s; v = pv[v]) {
				int u = pv[v], e = pe[v];
				graph[u][e].flow -= add;
				graph[v][graph[u][e].rev].flow += add;
			}
			flow += add;
			cost += add * d[t];
		}
		return {cost, flow};
	}
};

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
