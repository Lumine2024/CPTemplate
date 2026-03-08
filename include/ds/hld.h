#pragma once
#include "seg.h"

template<class Info>
concept HLDInfo = requires(Info a, Info b) {
	Info{};
	Info(a);
	{ a + b } -> same_as<Info>;
};

template<class Applier, class Info>
concept HLDApplier = requires(const Applier src, Info &dst) {
	{ src.apply(dst) } -> same_as<void>;
};

template<HLDInfo Info> struct HLDNode {
	Info w;
	vector<int> e;
};

template<HLDInfo Info, class Applier = Info>
	requires(HLDApplier<Applier, Info> && SegInfo<Info, Applier>)
struct HLD {
	using Node = HLDNode<Info>;
	explicit HLD(const vector<Node> &g, int r = 0) : nodes(g.size()) {
		dfs1(g, r, -1);
		int now = 0;
		dfs2(g, r, -1, now, r);
		vector<Info> nums(g.size());
		for(int i = 0; i < static_cast<int>(g.size()); ++i) {
			nums[nodes[i].dfn] = g[i].w;
		}
		seg.assign(nums);
	}
	explicit HLD(const vector<vector<int>> &edges, const vector<Info> &weights,
				 int r = 0)
		: HLD(build_nodes(edges, weights), r) {}
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
	void modify(int x, const Applier &v) {
		seg.update(nodes[x].dfn, v);
	}
	Info query_path(int u, int v) const {
		Info ans{};
		while(nodes[u].toc != nodes[v].toc) {
			if(nodes[nodes[u].toc].dep < nodes[nodes[v].toc].dep) {
				swap(u, v);
			}
			int top = nodes[u].toc;
			ans = ans + seg.query(nodes[top].dfn, nodes[u].dfn + 1);
			u = nodes[top].fa;
		}
		if(nodes[u].dep < nodes[v].dep) swap(u, v);
		ans = ans + seg.query(nodes[v].dfn, nodes[u].dfn + 1);
		return ans;
	}
	Info query_subtree(int x) const {
		return seg.query(nodes[x].dfn, nodes[x].dfn + nodes[x].sz);
	}
	Info query_dfn(int l, int r) const {
		return seg.query(l, r);
	}
	int dfn(int x) const {
		return nodes[x].dfn;
	}
	int size(int x) const {
		return nodes[x].sz;
	}

private:
	struct _Node {
		int dep, fa, toc, dfn, sz, hs;
	};
	vector<_Node> nodes;
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
			nodes[x].dep = 0;
		} else {
			nodes[x].dep = nodes[fa].dep + 1;
		}
		nodes[x].fa = fa;
		nodes[x].sz = 1;
		nodes[x].hs = -1;
		for(int i = 0; i < static_cast<int>(g[x].e.size()); ++i) {
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
		if(nodes[x].hs == -1) return;
		dfs2(g, nodes[x].hs, x, dfn, toc);
		for(int i = 0; i < static_cast<int>(g[x].e.size()); ++i) {
			int next = g[x].e[i];
			if(next != nodes[x].hs && next != fa) {
				dfs2(g, next, x, dfn, next);
			}
		}
	}
};
