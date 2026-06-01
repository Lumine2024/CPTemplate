#pragma once
#include "geo/basic.h"

struct LiChao {
	vector<LineSeg> lines;
	vector<array<ll, 4>> raw;
	explicit LiChao(int ma) : id(ma * 4, -1), n(ma) {}
	void addline(int x1, int x2, int y1, int y2) {
		if(x1 > x2) {
			swap(x1, x2);
			swap(y1, y2);
		}
		LineSeg ls({ld(x1), ld(y1)}, {ld(x2), ld(y2)});
		int i = lines.size();
		lines.push_back(ls);
		raw.push_back({x1, x2, y1, y2});
		_update(i, min(x1, x2), max(x1, x2), 0, 0, n - 1);
	}
	int query(int k) const {
		return _query(k, 0, 0, n - 1);
	}

private:
	vector<int> id;
	int n;
	pair<__int128, __int128> _calc(int i, int x) const {
		auto [x1, x2, y1, y2] = raw[i];
		if(x1 == x2) return {max(y1, y2), 1};
		__int128 den = x2 - x1;
		__int128 num = (__int128)y1 * den + (__int128)(y2 - y1) * (x - x1);
		return {num, den};
	}
	bool _better(int a, int b, int x) const {
		if(b == -1) return true;
		if(a == -1) return false;
		auto [na, da] = _calc(a, x);
		auto [nb, db] = _calc(b, x);
		__int128 lhs = na * db, rhs = nb * da;
		if(lhs != rhs) return lhs > rhs;
		return a < b;
	}
	void _update(int i, int ul, int ur, int u, int rl, int rr) {
		int mid = (rl + rr) / 2, ls = u * 2 + 1, rs = u * 2 + 2;
		if(ul <= rl && ur >= rr) {
			if(id[u] == -1) {
				id[u] = i;
				return;
			}
			if(_better(i, id[u], mid)) swap(i, id[u]);
			if(rl == rr) return;
			if(_better(i, id[u], rl)) _update(i, ul, ur, ls, rl, mid);
			if(_better(i, id[u], rr)) _update(i, ul, ur, rs, mid + 1, rr);
		} else {
			if(rl == rr) return;
			if(ul <= mid) _update(i, ul, ur, ls, rl, mid);
			if(mid < ur) _update(i, ul, ur, rs, mid + 1, rr);
		}
	}
	int _query(int k, int u, int rl, int rr) const {
		int ret = id[u];
		if(rl == rr) return ret;
		int mid = (rl + rr) / 2, ls = u * 2 + 1, rs = u * 2 + 2;
		int child =
			(k <= mid) ? _query(k, ls, rl, mid) : _query(k, rs, mid + 1, rr);
		if(_better(child, ret, k)) ret = child;
		return ret;
	}
};
