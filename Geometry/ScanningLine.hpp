#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

struct Rectangle {
	int x1, x2, y1, y2;
};

struct Event {
	int delta, y, l, r;
};

struct SegTree_SL {
	SegTree_SL(const vector<int> &_xs) : nodes(4 * _xs.size()), xs(_xs) {
		int n = _xs.size();
		_build(0, 0, n);
	}
	int query() const {
		return nodes[0].len;
	}
	// 注意左闭右开
	void update(int l, int r, int v) {
		_update(0, l, r, v);
	}
private:
	struct Node {
		int l, r, cnt, len;
	};
	vector<Node> nodes;
	vector<int> xs;
	void _pushup(int u) {
		if(nodes[u].cnt > 0) {
			nodes[u].len = xs[nodes[u].r] - xs[nodes[u].l];
		} else if(nodes[u].r - nodes[u].l == 1) {
			nodes[u].len = 0;
		} else {
			int lson = (u << 1) + 1, rson = (u << 1) + 2;
			nodes[u].len = nodes[lson].len + nodes[rson].len;
		}
	}
	void _build(int u, int l, int r) {
		nodes[u] = {l, r, 0, 0};
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

ll scanning_line(const vector<Rectangle> &rects) {
	int n = rects.size();
	vector<int> xs(2 * n);
	vector<Event> events(2 * n);
	for(int i = 0; i < n; ++i) {
		xs[2 * i] = rects[i].x1;
		xs[2 * i + 1] = rects[i].x2;
	}
	sort(xs.begin(), xs.end());
	xs.erase(unique(xs.begin(), xs.end()), xs.end());
	auto getid = [&](int x) -> int {
		return lower_bound(xs.begin(), xs.end(), x) - xs.begin();
	};
	for(int i = 0; i < n; ++i) {
		events[2 * i] = {1, rects[i].y1, getid(rects[i].x1), getid(rects[i].x2)}; // 注意这里不需要+1
		events[2 * i + 1] = {-1, rects[i].y2, getid(rects[i].x1), getid(rects[i].x2)};
	}
	sort(events.begin(), events.end(), [](const Event &a, const Event &b) {
		return a.y < b.y;
	});
	SegTree_SL seg(xs);
	ll lasty = events[0].y;
	ll ans = 0;
	for(auto &eve : events) {
		ans += (eve.y - lasty) * seg.query();
		seg.update(eve.l, eve.r, eve.delta);
		lasty = eve.y;
	}
	return ans;
}