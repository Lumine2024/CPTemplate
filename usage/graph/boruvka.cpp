// Standalone C++ file generated from graph/boruvka.hpp
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

// === ds/dsu.hpp ===

// 按秩合并
struct DSU {
	explicit DSU(int n) : fa(n), rk(n, 1) {
		iota(fa.begin(), fa.end(), 0);
	}
	int find(int x) {
		if(fa[x] != x) {
			fa[x] = find(fa[x]);
		}
		return fa[x];
	}
	bool is_connected(int x, int y) {
		return find(x) == find(y);
	}
	void connect(int x, int y) {
		x = find(x);
		y = find(y);
		if(x == y) return;
		if(rk[x] < rk[y]) {
			swap(x, y);
		}
		if(rk[x] == rk[y]) {
			rk[x]++;
		}
		fa[y] = x;
	}
private:
	vector<int> fa, rk;
};
// 随机合并
struct DSU_Random {
	explicit DSU_Random(int n) : fa(n) {
		iota(fa.begin(), fa.end(), 0);
	}
	int find(int x) {
		if(fa[x] != x) {
			fa[x] = find(fa[x]);
		}
		return fa[x];
	}
	bool is_connected(int x, int y) {
		return find(x) == find(y);
	}
	void connect(int x, int y) {
		int fx = find(x), fy = find(y);
		if(rnd() % 2) {
			fa[fx] = fy;
		} else {
			fa[fy] = fx;
		}
	}
private:
	static inline mt19937 rnd{ (unsigned int)chrono::steady_clock::now()
		.time_since_epoch().count() };
	vector<int> fa;
};

// === graph/common.hpp ===

struct Edge {
    int u, v;
    ll w;
};

// === graph/boruvka.hpp ===

ll boruvka(const vector<Edge> &edges, int n) {
	DSU dsu(n);
	ll ans = 0;
	int c = n;
	vector<Edge> mst(n);
	while(c > 1) {
		for(int i = 0; i < n; ++i) {
			if(dsu.find(i) != i) continue;
			mst[i] = Edge{-1, -1, inf};
		}
		for(auto [u, v, w] : edges) {
			int fu = dsu.find(u), fv = dsu.find(v);
			if(fu == fv) continue;
			if(mst[fu].w > w) {
				mst[fu] = Edge{u, v, w};
			}
			if(mst[fv].w > w) {
				mst[fv] = Edge{u, v, w};
			}
		}
		bool flag = false;
		for(int i = 0; i < n; ++i) {
			if(dsu.find(i) != i) continue;
			auto [u, v, w] = mst[i];
			if(w == inf) return inf;
			if(!dsu.is_connected(u, v)) {
				dsu.connect(u, v);
				ans += w;
				--c;
				flag = true;
			}
		}
		if(!flag) {
			return inf;
		}
	}
	return ans;
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
