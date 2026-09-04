#pragma once
#include "common.h"

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
	// make fa[find(y)] = find(x)
	void directed_connect(int x, int y) {
		x = find(x);
		y = find(y);
		if(x == y) return;
		fs[x] -= fs[y];
		fs[y] = x;
	}

private:
	vector<int> fs; // fa or size
};
