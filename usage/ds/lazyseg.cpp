#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;

template<class T1, class T2, class F> bool chkf(T1 &x, const T2 &y, F &&f) {
	if(f(static_cast<T1>(y), x)) {
		x = static_cast<T1>(y);
		return true;
	}
	return false;
}
template<class T1, class T2> bool chkmin(T1 &x, const T2 &y) {
	return chkf(x, y, less<T1>{});
}
template<class T1, class T2> bool chkmax(T1 &x, const T2 &y) {
	return chkf(x, y, greater<T1>{});
}

// clang-format off
template<class Info, class Tag>
concept SegInfoTag = requires(Info a, Info b, Tag c, Tag d, int l, int r) {
	Info{};
	Tag{};
	{ a + b } -> same_as<Info>;
	{ c.apply(a, l, r) } -> same_as<void>;
	{ c.apply(d, l, r) } -> same_as<void>;
	{ c.empty() } -> same_as<bool>;
	{ c.clear() } -> same_as<void>;
} && is_same_v<Info, typename vector<Info>::value_type>
  && is_same_v<Tag, typename vector<Tag>::value_type>;
template<class Info, class Tag> requires(SegInfoTag<Info, Tag>)
struct LazySegTree {
	// clang-format on
	LazySegTree() : n(0) {}
	explicit LazySegTree(int n_) : n(n_), info(4 * n_), tag(4 * n_) {}
	explicit LazySegTree(const vector<Info> &v)
		: n(v.size()), info(4 * v.size()), tag(4 * v.size()) {
		_build(v, 0, 0, n);
	}
	void assign(int n_) {
		n = n_;
		info.assign(4 * n_, Info{});
		tag.assign(4 * n_, Tag{});
	}
	void assign(const vector<Info> &v) {
		n = v.size();
		info.assign(4 * v.size(), Info{});
		tag.assign(4 * v.size(), Tag{});
		_build(v, 0, 0, n);
	}
	Info query(int l, int r) {
		return _query(l, r, 0, 0, n);
	}
	void update(int l, int r, const Tag &t) {
		_update(l, r, t, 0, 0, n);
	}

private:
	int n;
	vector<Info> info;
	vector<Tag> tag;
	void _build(const vector<Info> &v, int u, int rl, int rr) {
		if(rr - rl == 1) {
			info[u] = v[rl];
			return;
		}
		int mid = (rl + rr) / 2, ls = u * 2 + 1, rs = u * 2 + 2;
		_build(v, ls, rl, mid);
		_build(v, rs, mid, rr);
		info[u] = info[ls] + info[rs];
	}
	void _pushdown(int u, int rl, int rr) {
		if(tag[u].empty()) return;
		int mid = (rl + rr) / 2, ls = u * 2 + 1, rs = u * 2 + 2;
		tag[u].apply(info[ls], rl, mid);
		tag[u].apply(info[rs], mid, rr);
		tag[u].apply(tag[ls], rl, mid);
		tag[u].apply(tag[rs], mid, rr);
		tag[u].clear();
	}
	Info _query(int ql, int qr, int u, int rl, int rr) {
		if(ql <= rl && qr >= rr) return info[u];
		_pushdown(u, rl, rr);
		Info ret{};
		int mid = (rl + rr) / 2, ls = u * 2 + 1, rs = u * 2 + 2;
		if(ql < mid) ret = ret + _query(ql, qr, ls, rl, mid);
		if(qr > mid) ret = ret + _query(ql, qr, rs, mid, rr);
		return ret;
	}
	void _update(int ul, int ur, const Tag &t, int u, int rl, int rr) {
		if(ul <= rl && ur >= rr) {
			t.apply(info[u], rl, rr);
			t.apply(tag[u], rl, rr);
			return;
		}
		_pushdown(u, rl, rr);
		int mid = (rl + rr) / 2, ls = u * 2 + 1, rs = u * 2 + 2;
		if(ul < mid) _update(ul, ur, t, ls, rl, mid);
		if(ur > mid) _update(ul, ur, t, rs, mid, rr);
		info[u] = info[ls] + info[rs];
	}
};

struct Info {
	Info() {}
	Info operator+(const Info &i) const {}
};
struct Tag {
	Tag() {}
	bool empty() const {}
	void clear() {}
	void apply(Info &dst, int l, int r) const {}
	void apply(Tag &dst, int l, int r) const {}
};

inline void solve() {}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int t = 1;
	// cin >> t;
	while(t--) {
		solve();
	}
	return 0;
}
