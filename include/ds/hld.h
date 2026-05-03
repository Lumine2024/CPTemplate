#pragma once
#include "ds/seg.h"

template<class Info>
concept HldInfo = requires(Info a, Info b) {
	Info{};
	Info(a);
	{ a + b } -> same_as<Info>;
};

template<class Applier, class Info>
concept HldApplier = requires(const Applier src, Info &dst) {
	{ src.apply(dst) } -> same_as<void>;
};

template<HldInfo Info> struct HldNode {
	Info w;
	vector<int> e;
};

template<HldInfo Info, class Applier = Info>
	requires(HldApplier<Applier, Info> && SegInfo<Info, Applier>)
struct HLD {
	using Node = HldNode<Info>;
	explicit HLD(const vector<Node> &g, int r = 0)
		: dep(g.size()), fa(g.size()), toc(g.size()), dfn_order(g.size()),
		  sz(g.size()), hs(g.size(), -1) {
		dfs1(g, r, -1);
		int now = 0;
		dfs2(g, r, -1, now, r);
		vector<Info> nums(g.size());
		for(int i = 0; i < static_cast<int>(g.size()); ++i) {
			nums[dfn_order[i]] = g[i].w;
		}
		seg.assign(nums);
	}
	explicit HLD(const vector<vector<int>> &edges, const vector<Info> &weights,
				 int r = 0)
		: HLD(build_nodes(edges, weights), r) {}
	int lca(int u, int v) const {
		while(toc[u] != toc[v]) {
			if(dep[toc[u]] < dep[toc[v]]) {
				v = fa[toc[v]];
			} else {
				u = fa[toc[u]];
			}
		}
		return dep[u] < dep[v] ? u : v;
	}
	void modify(int x, const Applier &v) {
		seg.update(dfn_order[x], v);
	}
	Info query_path(int u, int v) const {
		Info ans{};
		while(toc[u] != toc[v]) {
			if(dep[toc[u]] < dep[toc[v]]) {
				swap(u, v);
			}
			int top = toc[u];
			ans = ans + seg.query(dfn_order[top], dfn_order[u] + 1);
			u = fa[top];
		}
		if(dep[u] < dep[v]) swap(u, v);
		ans = ans + seg.query(dfn_order[v], dfn_order[u] + 1);
		return ans;
	}
	Info query_subtree(int x) const {
		return seg.query(dfn_order[x], dfn_order[x] + sz[x]);
	}
	Info query_dfn(int l, int r) const {
		return seg.query(l, r);
	}
	int dfn(int x) const {
		return dfn_order[x];
	}
	int size(int x) const {
		return sz[x];
	}

private:
	vector<int> dep, fa, toc, dfn_order, sz, hs;
	SegTree<Info, Applier> seg;
	static vector<Node> build_nodes(const vector<vector<int>> &edges,
									const vector<Info> &weights) {
		vector<Node> g(edges.size());
		for(int i = 0; i < static_cast<int>(edges.size()); ++i) {
			g[i].w = weights[i];
			g[i].e = edges[i];
		}
		return g;
	}
	void dfs1(const vector<Node> &g, int x, int fa) {
		if(fa == -1) {
			dep[x] = 0;
		} else {
			dep[x] = dep[fa] + 1;
		}
		this->fa[x] = fa;
		sz[x] = 1;
		hs[x] = -1;
		for(int i = 0; i < static_cast<int>(g[x].e.size()); ++i) {
			int next = g[x].e[i];
			if(next == fa) continue;
			dfs1(g, next, x);
			sz[x] += sz[next];
			if(hs[x] == -1 || sz[hs[x]] < sz[next]) {
				hs[x] = next;
			}
		}
	}
	void dfs2(const vector<Node> &g, int x, int fa, int &dfn, int toc) {
		dfn_order[x] = dfn++;
		this->toc[x] = toc;
		if(hs[x] == -1) return;
		dfs2(g, hs[x], x, dfn, toc);
		for(int i = 0; i < static_cast<int>(g[x].e.size()); ++i) {
			int next = g[x].e[i];
			if(next != hs[x] && next != fa) {
				dfs2(g, next, x, dfn, next);
			}
		}
	}
};
