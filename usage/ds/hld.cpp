#include "common.h"

template<class Info>
concept SegInfo = requires(Info a, Info b) {
	Info{};
	{ a + b } -> same_as<Info>;
	{ a.update(b) } -> same_as<void>;
} && is_same_v<Info, typename vector<Info>::value_type>;

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
	vector<_Node> nodes;
	vector<int> nfd;
	SegTree<HLDInfo> seg;
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
			if(nodes[x].hs == -1 || nodes[nodes[x].hs].sz < nodes[next].sz) {
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
