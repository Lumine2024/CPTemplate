// Standalone C++ file generated from ds/hld.hpp
// Can be directly submitted to online judges

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;

inline constexpr ll modulo = 998244353, g = 3, inf = 0x3f3f3f3f3f3f3f3f;
inline constexpr int maxn = 100005, infint = 0x3f3f3f3f;
inline constexpr ld eps = 1e-9l, pi = 3.14159265358979323846264338327950288l, infld = 1e12l;

inline ll qpow(ll x, ll n) {
    ll ret = 1;
    for(; n != 0; n >>= 1, x = x * x % modulo) {
        if(n & 1) ret = ret * x % modulo;
    }
    return ret;
}

template<class T, class F> bool chkf(T &x, const T &y, F &&f) {
    if(f(y, x)) {
        x = y;
        return true;
    }
    return false;
}
template<class T> bool chkmin(T &x, const T &y) {
    return chkf(x, y, less{});
}
template<class T> bool chkmax(T &x, const T &y) {
    return chkf(x, y, greater{});
}

// === ds/seg.hpp ===

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

// === ds/hld.hpp ===

struct HLDInfo {
	ll val;
	explicit HLDInfo(ll v) : val(v) {}
	HLDInfo() : val(0) {}
	void update(HLDInfo &dst) const {
		dst.val = val;
	}
	HLDInfo operator+(const HLDInfo &x) const {
		return HLDInfo(val + x.val);
	}
};

struct Node {
	ll w;
	vector<int> e;
};
struct HLD {
	explicit HLD(const vector<Node> &g, int r = 0)
		: nodes(g.size()), nfd(g.size()) {
		dfs1(g, r, -1);
		int now_index = 0;
		dfs2(g, r, -1, now_index, r);
		vector<HLDInfo> nums(g.size());
		for(int i = 0; i < g.size(); ++i) {
			nums[nodes[i].dfn] = HLDInfo{g[i].w};
		}
		seg.assign(nums);
	}
	int lca(int u, int v) const {
		while(nodes[u].toc != nodes[v].toc) {
			if(nodes[nodes[u].toc].dep < nodes[nodes[v].toc].dep) {
				v = nodes[nodes[v].toc].fa;
			} else {
				u = nodes[nodes[u].toc].fa;
			}
		}
		return nodes[u].dep < nodes[v].dep ? u : v;
	}
	void modify(int x, ll v) {
		seg.update(nodes[x].dfn, HLDInfo{v});
	}
	ll query_sum(int u, int v) const {
		int lca_node = lca(u, v);
		auto query_to_lca = [&](int point) -> ll {
			ll ans = 0;
			for(; nodes[point].toc != nodes[lca_node].toc;
				point = nodes[nodes[point].toc].fa) {
				int pos1 = nodes[point].dfn;
				int pos2 = nodes[nodes[point].toc].dfn;
				ans += seg.query(pos2, pos1 + 1).val;
			}
			int pos1 = nodes[lca_node].dfn;
			int pos2 = nodes[point].dfn;
			ans += seg.query(pos1 + 1, pos2 + 1).val;
			return ans;
		};
		ll ans = query_to_lca(u);
		ans += query_to_lca(v);
		int lca_pos = nodes[lca_node].dfn;
		ans += seg.query(lca_pos, lca_pos + 1).val;
		return ans;
	}
private:
	struct _Node {
		int dep, fa, toc, dfn, sz, hs;
	};
	void dfs1(const vector<Node> &g, int x, int fa) {
		if(fa == -1) {
			nodes[x].dep = 0;
		} else {
			nodes[x].dep = nodes[fa].dep + 1;
		}
		nodes[x].fa = fa;
		nodes[x].sz = 1;
		nodes[x].hs = -1;
		for(int i = 0; i < g[x].e.size(); ++i) {
			int next = g[x].e[i];
			if(next == fa) continue;
			dfs1(g, next, x);
			nodes[x].sz += nodes[next].sz;
			if(nodes[x].hs == -1 ||
				nodes[nodes[x].hs].sz < nodes[next].sz) {
				nodes[x].hs = next;
			}
		}
	}
	void dfs2(const vector<Node> &g, int x, int fa, int &dfn, int toc) {
		nodes[x].dfn = dfn++;
		nodes[x].toc = toc;
		if(nodes[x].hs != -1) {
			dfs2(g, nodes[x].hs, x, dfn, toc);
			for(int i = 0; i < g[x].e.size(); ++i) {
				int next = g[x].e[i];
				if(next != nodes[x].hs && next != fa) {
					dfs2(g, next, x, dfn, next);
				}
			}
		}
	}
	vector<_Node> nodes;
	vector<int> nfd;
	SegTree<HLDInfo> seg;
};

// Example usage:
inline void solve() {
    // Add your solution code here using the template above
}

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
