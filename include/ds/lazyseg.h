#pragma once
#include "common.h"

template<class Info, class Tag>
concept SegInfoTag = requires(Info a, Info b, Tag c, Tag d, int l, int r,
							  vector<Info> vi, vector<Tag> vt) {
	Info{};
	Tag{};
	{ a + b } -> same_as<Info>;
	{ c.apply(a, l, r) } -> same_as<void>;
	{ c.apply(d, l, r) } -> same_as<void>;
	{ c.empty() } -> same_as<bool>;
	{ c.clear() } -> same_as<void>;
	{ vi[l] } -> same_as<Info &>;
	{ vt[l] } -> same_as<Tag &>;
};
template<class Info, class Tag>
	requires(SegInfoTag<Info, Tag>)
struct LazySegTree {
	LazySegTree() : n(0) {}
	explicit LazySegTree(int n_) : n(n_), info(4 * n_), tag(4 * n_) {}
	explicit LazySegTree(const vector<Info> &v)
		: n(v.size()), info(4 * v.size()), tag(4 * v.size()) {
		[&](auto &&bld) {
			bld(bld, v, 0, 0, n);
		}([&](auto &&bld, const vector<Info> &v, int u, int rl,
			  int rr) -> void {
			if(rr - rl == 1) {
				info[u] = v[rl];
				return;
			}
			int mid = (rl + rr) / 2, ls = u * 2 + 1, rs = u * 2 + 2;
			bld(bld, v, ls, rl, mid);
			bld(bld, v, rs, mid, rr);
			info[u] = info[ls] + info[rs];
		});
	}
	Info query(int l, int r) {
		return [&](auto &&qry) {
			return qry(qry, l, r, 0, 0, n);
		}([&](auto &&qry, int ql, int qr, int u, int rl, int rr) -> Info {
			if(ql <= rl && qr >= rr) return info[u];
			_pushdown(u, rl, rr);
			Info ret{};
			int mid = (rl + rr) / 2, ls = u * 2 + 1, rs = u * 2 + 2;
			if(ql < mid) ret = ret + qry(qry, ql, qr, ls, rl, mid);
			if(qr > mid) ret = ret + qry(qry, ql, qr, rs, mid, rr);
			return ret;
		});
	}
	void update(int l, int r, const Tag &t) {
		[&](auto &&upd) {
			upd(upd, l, r, t, 0, 0, n);
		}([&](auto &&upd, int ul, int ur, const Tag &t, int u, int rl,
			  int rr) -> void {
			if(ul <= rl && ur >= rr) {
				t.apply(info[u], rl, rr);
				t.apply(tag[u], rl, rr);
				return;
			}
			_pushdown(u, rl, rr);
			int mid = (rl + rr) / 2, ls = u * 2 + 1, rs = u * 2 + 2;
			if(ul < mid) upd(upd, ul, ur, t, ls, rl, mid);
			if(ur > mid) upd(upd, ul, ur, t, rs, mid, rr);
			info[u] = info[ls] + info[rs];
		});
	}

private:
	int n;
	vector<Info> info;
	vector<Tag> tag;
	void _pushdown(int u, int rl, int rr) {
		if(tag[u].empty()) return;
		int mid = (rl + rr) / 2, ls = u * 2 + 1, rs = u * 2 + 2;
		tag[u].apply(info[ls], rl, mid);
		tag[u].apply(info[rs], mid, rr);
		tag[u].apply(tag[ls], rl, mid);
		tag[u].apply(tag[rs], mid, rr);
		tag[u].clear();
	}
};
