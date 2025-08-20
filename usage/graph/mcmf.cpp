// Standalone C++ file generated from graph/mcmf.hpp
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

// === graph/mcmf.hpp ===

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
