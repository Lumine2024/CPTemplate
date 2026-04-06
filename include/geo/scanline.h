#pragma once
#include "geo/basic.h"

struct Rectangle {
	Point p1, p2;
};
struct Event {
	int delta, l, r;
	ld y;
};
struct SegTree_SL {
	SegTree_SL(const vector<ld> &_xs) : nodes(4 * _xs.size()), xs(_xs) {
		int n = xs.size();
		_build(0, 0, n);
	}
	ld query() const {
		return nodes[0].len;
	}
	// 注意左闭右开
	void update(int l, int r, int v) {
		_update(0, l, r, v);
	}

private:
	struct Node {
		int l, r, cnt;
		ld len;
	};
	vector<Node> nodes;
	vector<ld> xs;
	void _pushup(int u) {
		if(nodes[u].cnt > 0) {
			nodes[u].len = xs[nodes[u].r] - xs[nodes[u].l];
		} else if(nodes[u].r - nodes[u].l == 1) {
			nodes[u].len = 0.0l;
		} else {
			int lson = (u << 1) + 1, rson = (u << 1) + 2;
			nodes[u].len = nodes[lson].len + nodes[rson].len;
		}
	}
	void _build(int u, int l, int r) {
		nodes[u] = {l, r, 0, 0.0l};
		if(r - l > 1) {
			int mid = (l + r) >> 1, lson = (u << 1) + 1, rson = (u << 1) + 2;
			_build(lson, l, mid);
			_build(rson, mid, r);
		}
	}
	void _update(int u, int l, int r, int v) {
		if(nodes[u].l >= r || nodes[u].r <= l) return;
		if(nodes[u].l >= l && nodes[u].r <= r) {
			nodes[u].cnt += v;
			_pushup(u);
			return;
		}
		int lson = (u << 1) + 1, rson = (u << 1) + 2;
		_update(lson, l, r, v);
		_update(rson, l, r, v);
		_pushup(u);
	}
};
ld scanline(const vector<Rectangle> &rects) {
	int n = rects.size();
	vector<ld> xs(2 * n);
	vector<Event> events(2 * n);
	for(int i = 0; i < n; ++i) {
		xs[2 * i] = rects[i].p1.x;
		xs[2 * i + 1] = rects[i].p2.x;
	}
	sort(xs.begin(), xs.end());
	xs.erase(unique(xs.begin(), xs.end()), xs.end());
	auto getid = [&](ld x) -> int {
		return lower_bound(xs.begin(), xs.end(), x) - xs.begin();
	};
	for(int i = 0; i < n; ++i) {
		events[2 * i] = {1, getid(rects[i].p1.x), getid(rects[i].p2.x),
						 rects[i].p1.y};
		events[2 * i + 1] = {-1, getid(rects[i].p1.x), getid(rects[i].p2.x),
							 rects[i].p2.y};
	}
	sort(events.begin(), events.end(),
		 [](const Event &a, const Event &b) { return cmp(a.y, b.y) == -1; });
	SegTree_SL seg(xs);
	ld lasty = events[0].y;
	ld ans = 0.0l;
	for(auto &e : events) {
		ans += seg.query() * (e.y - lasty);
		seg.update(e.l, e.r, e.delta);
		lasty = e.y;
	}
	return ans;
}
