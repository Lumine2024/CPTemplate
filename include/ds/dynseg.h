#pragma once
#include "common.h"

template<class Info, class Applier>
concept DynSegInfo = requires(Info a, Info b, const Applier src) {
	Info{};
	Info(a);
	{ a + b } -> same_as<Info>;
	{ src.apply(a) } -> same_as<void>;
};

template<class Info, class Applier>
	requires(DynSegInfo<Info, Applier>)
struct DynSegTree {
	explicit DynSegTree(ll _n) : n(_n), info(1, _(0, _n)) {}
	void update(ll x, const Applier &src) {
		[&](auto &&upd) {
			upd(upd, x, src, 0);
		}([&](auto &&upd, ll x, const Applier &src, ll u) -> void {
			if(info[u].l == info[u].r - 1) {
				src.apply(info[u].info);
				return;
			}
			ll mid = (info[u].l + info[u].r) / 2;
			if(x < mid) {
				if(info[u].ls == -1) {
					info[u].ls = info.size();
					info.emplace_back(info[u].l, mid);
				}
				upd(upd, x, src, info[u].ls);
			} else {
				if(info[u].rs == -1) {
					info[u].rs = info.size();
					info.emplace_back(mid, info[u].r);
				}
				upd(upd, x, src, info[u].rs);
			}
			info[u].info = Info{};
			if(info[u].ls != -1)
				info[u].info = info[u].info + info[info[u].ls].info;
			if(info[u].rs != -1)
				info[u].info = info[u].info + info[info[u].rs].info;
		});
	}
	Info query(ll l, ll r) const {
		return [&](auto &&qry) {
			return qry(qry, l, r, 0);
		}([&](auto &&qry, ll ql, ll qr, ll u) -> Info {
			if(ql <= info[u].l && qr >= info[u].r) return info[u].info;
			Info ret{};
			ll mid = (info[u].l + info[u].r) / 2;
			if(ql < mid && info[u].ls != -1)
				ret = ret + qry(qry, ql, qr, info[u].ls);
			if(qr > mid && info[u].rs != -1)
				ret = ret + qry(qry, ql, qr, info[u].rs);
			return ret;
		});
	}

private:
	struct _ {
		Info info;
		ll l, r, ls, rs;
		_() : info{}, l(0), r(0), ls(-1), rs(-1) {}
		_(ll _l, ll _r) : info{}, l(_l), r(_r), ls(-1), rs(-1) {}
	};
	vector<_> info;
	ll n;
};
