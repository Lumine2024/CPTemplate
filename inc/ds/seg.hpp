#pragma once
#include "constants.hpp"

template<class Info> concept SegInfo = requires(Info a, Info b) {
	{ a + b } -> same_as<Info>;
	{ a.update(b) } -> same_as<void>;
};

template<SegInfo Info> struct SegTree {
public:
	SegTree() : n(0) {}
	explicit SegTree(int sz) : n(sz), info(sz * 4, Info()) {}
	explicit SegTree(const vector<Info> &v) : n(v.size()), info(v.size() * 4) {
		_build(v, 0, 0, n);
	}
	void assign(int sz) {
		n = sz;
		info.assign(n * 4, Info());
	}
	void assign(const vector<Info> &v) {
		n = v.size();
		info.assign(n * 4, Info());
		_build(v, 0, 0, n);
	}
	Info query(int l, int r) const {
		if(l == r) return Info();
		return _query(l, r, 0, 0, n);
	}
	void update(int x, const Info &v) {
		_update(x, v, 0, 0, n);
	}
private:
	int n;
	vector<Info> info;
	void _build(const vector<Info> &v, int u, int rl, int rr) {
		if(rl == rr - 1) {
			info[u] = v[rl];
			return;
		}
		int mid = (rl + rr) / 2, ls = u * 2 + 1, rs = u * 2 + 2;
		_build(v, ls, rl, mid);
		_build(v, rs, mid, rr);
		info[u] = info[ls] + info[rs];
	}
	Info _query(int ql, int qr, int u, int rl, int rr) const {
		if(ql <= rl && qr >= rr) return info[u];
		int mid = (rl + rr) >> 1, ls = u * 2 + 1, rs = u * 2 + 2;
		Info res{};
		if(ql < mid) res = res + _query(ql, qr, ls, rl, mid);
		if(qr > mid) res = res + _query(ql, qr, rs, mid, rr);
		return res;
	}
	void _update(int x, const Info &v, int u, int rl, int rr) {
		if(rl == rr - 1) {
			v.update(info[u]);
			return;
		}
		int mid = (rl + rr) >> 1, ls = u * 2 + 1, rs = u * 2 + 2;
		if(x < mid) _update(x, v, ls, rl, mid);
		else _update(x, v, rs, mid, rr);
		info[u] = info[ls] + info[rs];
	}
};

template<class Info, class Tag> concept LazySegInfoTag = requires(Info a, Info b, Tag c, Tag d, int l, int r) {
	{ a + b } -> same_as<Info>;
	{ a.update(b, l, r) } -> same_as<void>;
	{ a.update(c) } -> same_as<void>;
	{ c.apply(a, l, r) } -> same_as<void>;
	{ c.apply(d) } -> same_as<void>;
	{ c.clear() } -> same_as<void>;
	{ c.is_null() } -> same_as<bool>;
};
template<class Info, class Tag> requires LazySegInfoTag<Info, Tag> struct LazySegTree {
	LazySegTree() : LazySegTree(0) {}
	explicit LazySegTree(int n) : n(n), info(4 * n, Info{}), tag(4 * n, Tag{}) {}
	explicit LazySegTree(const vector<Info> &v) : n(v.size()), info(4 * n), tag(4 * n) {
		_build(v, 0, 0, n);
	}
	void assign(int _n) {
		n = _n;
		info.assign(4 * n, Info{});
		tag.assign(4 * n, Tag{});
	}
	void assign(const vector<Info> &v) {
		n = v.size();
		info.assign(4 * n, Info{});
		tag.assign(4 * n, Tag{});
		_build(v, 0, 0, n);
	}
	Info query(int l, int r) {
		return _query(l, r, 0, 0, n);
	}
	void update(int l, int r, const Info &dv) {
		_update(l, r, dv, 0, 0, n);
	}
private:
	int n;
	vector<Info> info;
	vector<Tag> tag;
	void _build(const vector<Info> &v, int u, int rl, int rr) {
		if(rl + 1 == rr) {
			info[u] = v[rl];
			return;
		}
		int mid = (rl + rr) / 2, ls = u * 2 + 1, rs = u * 2 + 2;
		_build(v, ls, rl, mid);
		_build(v, rs, mid, rr);
		info[u] = info[ls] + info[rs];
	}
	void _pushdown(int u, int rl, int rr) {
		if(tag[u].is_null()) return;
		int mid = (rl + rr) / 2, ls = u * 2 + 1, rs = u * 2 + 2;
		tag[u].apply(info[ls], rl, mid);
		tag[u].apply(info[rs], mid, rr);
		tag[u].apply(tag[ls]);
		tag[u].apply(tag[rs]);
		tag[u].clear();
	}
	Info _query(int ql, int qr, int u, int rl, int rr) {
		if(ql <= rl && rr <= qr) return info[u];
		_pushdown(u, rl, rr);
		int mid = (rl + rr) / 2, ls = u * 2 + 1, rs = u * 2 + 2;
		Info ret{};
		if(ql < mid) {
			ret = ret + _query(ql, qr, ls, rl, mid);
		}
		if(qr > mid) {
			ret = ret + _query(ql, qr, rs, mid, rr);
		}
		return ret;
	}
	void _update(int ul, int ur, const Info &dv, int u, int rl, int rr) {
		if(ul <= rl && rr <= ur) {
			dv.update(info[u], rl, rr);
			dv.update(tag[u]);
			return;
		}
		_pushdown(u, rl, rr);
		int mid = (rl + rr) / 2, ls = u * 2 + 1, rs = u * 2 + 2;
		if(ul < mid) {
			_update(ul, ur, dv, ls, rl, mid);
		}
		if(ur > mid) {
			_update(ul, ur, dv, rs, mid, rr);
		}
		info[u] = info[ls] + info[rs];
	}
};

// 使用示例：区间加，区间和
/*
struct RangeAddTag;
struct RangeAddInfo {
	ll val;
	RangeAddInfo() : val(0) {}
	RangeAddInfo(ll v) : val(v) {}
	RangeAddInfo operator+(const RangeAddInfo &x) const {
		return RangeAddInfo{ val + x.val };
	}
	void update(RangeAddInfo &dst, int l, int r) const {
		dst.val += val * (r - l);
	}
	void update(RangeAddTag &dst) const;
};
struct RangeAddTag {
	ll val;
	RangeAddTag() : val(0) {}
	bool is_null() const {
		return val == 0;
	}
	void apply(RangeAddInfo &dst, int l, int r) const {
		dst.val += val * (r - l);
	}
	void apply(RangeAddTag &dst) const {
		dst.val += val;
	}
	void clear() {
		val = 0;
	}
};
void RangeAddInfo::update(RangeAddTag &dst) const {
	dst.val += val;
}
*/