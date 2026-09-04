#pragma once
#include "geo/int/basic.h"

struct RectangleInt {
	PointInt p1, p2;
};
struct EventInt {
	int d, l, r;
	ll y;
};
struct SegTree_SLInt {
	SegTree_SLInt(const vector<ll> &_xs)
		: l(4 * _xs.size()), r(4 * _xs.size()), cnt(4 * _xs.size()),
		  len(4 * _xs.size()), xs(_xs) {
		int n = xs.size();
		[&](auto &&bld) {
			bld(bld, 0, 0, n);
		}([&](auto &&bld, int u, int l, int r) -> void {
			this->l[u] = l;
			this->r[u] = r;
			cnt[u] = 0;
			len[u] = 0;
			if(r - l > 1) {
				int mid = (l + r) >> 1, lson = (u << 1) + 1,
					rson = (u << 1) + 2;
				bld(bld, lson, l, mid);
				bld(bld, rson, mid, r);
			}
		});
	}
	ll query() const {
		return len[0];
	}
	// 注意左闭右开
	void update(int l, int r, int v) {
		[&](auto &&upd) {
			upd(upd, 0, l, r, v);
		}([&](auto &&upd, int u, int l, int r, int v) -> void {
			if(this->l[u] >= r || this->r[u] <= l) return;
			if(this->l[u] >= l && this->r[u] <= r) {
				cnt[u] += v;
				_pushup(u);
				return;
			}
			int lson = (u << 1) + 1, rson = (u << 1) + 2;
			upd(upd, lson, l, r, v);
			upd(upd, rson, l, r, v);
			_pushup(u);
		});
	}

private:
	vector<int> l, r, cnt;
	vector<ll> len, xs;
	void _pushup(int u) {
		if(cnt[u] > 0) {
			len[u] = xs[r[u]] - xs[l[u]];
		} else if(r[u] - l[u] == 1) {
			len[u] = 0;
		} else {
			int lson = (u << 1) + 1, rson = (u << 1) + 2;
			len[u] = len[lson] + len[rson];
		}
	}
};
ll scanline(const vector<RectangleInt> &rs) {
	int n = rs.size();
	vector<ll> xs(2 * n);
	vector<EventInt> evs(2 * n);
	for(int i = 0; i < n; ++i) {
		xs[2 * i] = rs[i].p1.x;
		xs[2 * i + 1] = rs[i].p2.x;
	}
	sort(xs.begin(), xs.end());
	xs.erase(unique(xs.begin(), xs.end()), xs.end());
	auto getid = [&](ll x) -> int {
		return lower_bound(xs.begin(), xs.end(), x) - xs.begin();
	};
	for(int i = 0; i < n; ++i) {
		evs[2 * i] = {1, getid(rs[i].p1.x), getid(rs[i].p2.x), rs[i].p1.y};
		evs[2 * i + 1] = {-1, getid(rs[i].p1.x), getid(rs[i].p2.x), rs[i].p2.y};
	}
	sort(evs.begin(), evs.end(),
		 [](const EventInt &a, const EventInt &b) { return a.y < b.y; });
	SegTree_SLInt seg(xs);
	ll ly = evs[0].y;
	ll ans = 0;
	for(auto &e : evs) {
		ans += seg.query() * (e.y - ly);
		seg.update(e.l, e.r, e.d);
		ly = e.y;
	}
	return ans;
}
