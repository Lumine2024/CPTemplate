#pragma once
#include "common.h"

template<class Info, class Applier>
concept SegInfo =
	requires(Info a, Info b, const Applier src, vector<Info> vi, int u) {
		Info{};
		Info(a);
		{ a + b } -> same_as<Info>;
		{ src.apply(a) } -> same_as<void>;
		{ vi[u] } -> same_as<Info &>;
	};

template<class Info, class Applier>
	requires(SegInfo<Info, Applier>)
struct SegTree {
	SegTree() : n(0) {}
	explicit SegTree(int sz) : n(sz), info(sz * 4, Info()) {}
	explicit SegTree(const vector<Info> &v) : n(v.size()), info(v.size() * 4) {
		[&](auto &&bld) {
			bld(bld, v, 0, 0, n);
		}([&](auto &&bld, const vector<Info> &v, int u, int rl,
			  int rr) -> void {
			if(rl == rr - 1) {
				info[u] = v[rl];
				return;
			}
			int mid = (rl + rr) / 2, ls = u * 2 + 1, rs = u * 2 + 2;
			bld(bld, v, ls, rl, mid);
			bld(bld, v, rs, mid, rr);
			info[u] = info[ls] + info[rs];
		});
	}
	Info query(int l, int r) const {
		if(l >= r) return Info();
		return [&](auto &&qry) {
			return qry(qry, l, r, 0, 0, n);
		}([&](auto &&qry, int ql, int qr, int u, int rl, int rr) -> Info {
			if(ql <= rl && qr >= rr) return info[u];
			int mid = (rl + rr) / 2, ls = u * 2 + 1, rs = u * 2 + 2;
			Info ret{};
			if(ql < mid) ret = ret + qry(qry, ql, qr, ls, rl, mid);
			if(qr > mid) ret = ret + qry(qry, ql, qr, rs, mid, rr);
			return ret;
		});
	}
	void update(int x, const Applier &v) {
		[&](auto &&upd) {
			upd(upd, x, v, 0, 0, n);
		}([&](auto &&upd, int x, const Applier &v, int u, int rl,
			  int rr) -> void {
			if(rl == rr - 1) {
				v.apply(info[u]);
				return;
			}
			int mid = (rl + rr) >> 1, ls = u * 2 + 1, rs = u * 2 + 2;
			if(x < mid) upd(upd, x, v, ls, rl, mid);
			else upd(upd, x, v, rs, mid, rr);
			info[u] = info[ls] + info[rs];
		});
	}

private:
	int n;
	vector<Info> info;
};
