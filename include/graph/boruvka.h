#pragma once
#include "common.h"

constexpr ll inf = 0x3f3f3f3f3f3f3f3f;

struct DSU {
	explicit DSU(int n) : fs(n, -1) {}
	int find(int x) {
		if(fs[x] < 0) return x;
		return fs[x] = find(fs[x]);
	}
	bool is_connected(int x, int y) {
		return find(x) == find(y);
	}
	int size(int x) {
		return -fs[find(x)];
	}
	void connect(int x, int y) {
		x = find(x);
		y = find(y);
		if(x == y) return;
		int sx = size(x), sy = size(y);
		if(sx < sy) {
			fs[y] -= sx;
			fs[x] = y;
		} else {
			fs[x] -= sy;
			fs[y] = x;
		}
	}

private:
	vector<int> fs; // fa or size
};

struct Edge {
	int u, v;
	ll w;
};

ll boruvka(const vector<Edge> &edges, int n) {
	int m = edges.size();
	DSU dsu(n);
	ll ans = 0;
	int c = n;
	vector<int> mst(n);
	while(c > 1) {
		for(int i = 0; i < n; ++i) {
			if(dsu.find(i) == i) mst[i] = -1;
		}
		for(int i = 0; i < m; ++i) {
			auto [u, v, w] = edges[i];
			int fu = dsu.find(u), fv = dsu.find(v);
			if(fu == fv) continue;
			if(mst[fu] == -1 || edges[mst[fu]].w > w) mst[fu] = i;
			if(mst[fv] == -1 || edges[mst[fv]].w > w) mst[fv] = i;
		}
		bool flag = false;
		for(int i = 0; i < n; ++i) {
			if(dsu.find(i) != i || mst[i] == -1) continue;
			auto [u, v, w] = edges[mst[i]];
			if(!dsu.is_connected(u, v)) {
				dsu.connect(u, v);
				ans += w;
				--c;
				flag = true;
			}
		}
		if(!flag) return inf;
	}
	return ans;
}
