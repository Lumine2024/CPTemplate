#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

// 按秩合并
struct DSU {
	DSU(int n) : fa(n), rk(n, 1) {
		iota(fa.begin(), fa.end(), 0);
	}
	int find(int x) {
		if(fa[x] != x) {
			fa[x] = find(fa[x]);
		}
		return fa[x];
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
	bool is_connected(int x, int y) {
		return find(x) == find(y);
	}
private:
	vector<int> fa, rk;
};
// 随机合并
struct DSU_Random {
	DSU_Random(int n) : fa(n) {
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