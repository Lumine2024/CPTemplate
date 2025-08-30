
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


struct EK {
    struct Edge {
        int dst, rev;
        ll weight, flow;
        bool neg;
    };
    vector<vector<Edge>> graph;
    vector<int> pv, pe;
    vector<ll> mf, d;
    vector<bool> inq;
    int n;
    explicit EK(int _n) : n(_n), graph(_n), pv(_n, -1), pe(_n, -1), d(_n, inf), mf(_n, 0), inq(_n, false) {}
    void addedge(int u, int v, ll flow, ll weight) {
        int iu = graph[u].size(), iv = graph[v].size();
        graph[u].push_back({ v, iv, weight, flow, false });
        graph[v].push_back({ u, iu, -weight, 0, true });
    }
    pair<ll, ll> solve() {
        ll cost = 0, flow = 0;
        while(true) {
            for(int i = 0; i < n; ++i) {
                d[i] = inf;
                mf[i] = 0;
                inq[i] = false;
                pv[i] = -1;
                pe[i] = -1;
            }
            queue<int> q;
            q.push(0);
            d[0] = 0;
            mf[0] = inf;
            inq[0] = true;
            while(!q.empty()) {
                int u = q.front();
                q.pop();
                inq[u] = false;
                for(int i = 0; i < graph[u].size(); ++i) {
                    auto &e = graph[u][i];
                    int v = e.dst;
                    ll f = e.flow, w = e.weight;
                    if(f > 0 && chkmin(d[v], d[u] + w)) {
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
            if(mf[n - 1] <= 0) break;
            ll add = mf[n - 1];
            for(int v = n - 1; v != 0; v = pv[v]) {
                int u = pv[v], e = pe[v];
                graph[u][e].flow -= add;
                graph[v][graph[u][e].rev].flow += add;
            }
            flow += add;
            cost += add * d[n - 1];
        }
        return { cost, flow };
    }
};

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
