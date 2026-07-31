#pragma once
#include "geo/fp/basic.h"

struct Rectangle {
	Point p1, p2;
};
struct Event {
	int d, l, r;
	ld y;
};
struct SegTree_SL {
	SegTree_SL(const vector<ld> &_xs)
		: l(4 * _xs.size()), r(4 * _xs.size()), cnt(4 * _xs.size()),
		  len(4 * _xs.size()), xs(_xs) {
		int n = xs.size();
		_build(0, 0, n);
	}
	ld query() const {
		return len[0];
	}
	// 注意左闭右开
	void update(int l, int r, int v) {
		_update(0, l, r, v);
	}

private:
	vector<int> l, r, cnt;
	vector<ld> len, xs;
	void _pushup(int u) {
		if(cnt[u] > 0) {
			len[u] = xs[r[u]] - xs[l[u]];
		} else if(r[u] - l[u] == 1) {
			len[u] = 0.0l;
		} else {
			int lson = (u << 1) + 1, rson = (u << 1) + 2;
			len[u] = len[lson] + len[rson];
		}
	}
	void _build(int u, int l, int r) {
		this->l[u] = l;
		this->r[u] = r;
		cnt[u] = 0;
		len[u] = 0.0l;
		if(r - l > 1) {
			int mid = (l + r) >> 1, lson = (u << 1) + 1, rson = (u << 1) + 2;
			_build(lson, l, mid);
			_build(rson, mid, r);
		}
	}
	void _update(int u, int l, int r, int v) {
		if(this->l[u] >= r || this->r[u] <= l) return;
		if(this->l[u] >= l && this->r[u] <= r) {
			cnt[u] += v;
			_pushup(u);
			return;
		}
		int lson = (u << 1) + 1, rson = (u << 1) + 2;
		_update(lson, l, r, v);
		_update(rson, l, r, v);
		_pushup(u);
	}
};
ld scanline(const vector<Rectangle> &rs) {
	int n = rs.size();
	vector<ld> xs(2 * n);
	vector<Event> evs(2 * n);
	for(int i = 0; i < n; ++i) {
		xs[2 * i] = rs[i].p1.x;
		xs[2 * i + 1] = rs[i].p2.x;
	}
	sort(xs.begin(), xs.end());
	xs.erase(unique(xs.begin(), xs.end()), xs.end());
	auto getid = [&](ld x) -> int {
		return lower_bound(xs.begin(), xs.end(), x) - xs.begin();
	};
	for(int i = 0; i < n; ++i) {
		evs[2 * i] = {1, getid(rs[i].p1.x), getid(rs[i].p2.x), rs[i].p1.y};
		evs[2 * i + 1] = {-1, getid(rs[i].p1.x), getid(rs[i].p2.x), rs[i].p2.y};
	}
	sort(evs.begin(), evs.end(),
		 [](const Event &a, const Event &b) { return cmp(a.y, b.y) == -1; });
	SegTree_SL seg(xs);
	ld ly = evs[0].y;
	ld ans = 0.0l;
	for(auto &e : evs) {
		ans += seg.query() * (e.y - ly);
		seg.update(e.l, e.r, e.d);
		ly = e.y;
	}
	return ans;
}
