#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

struct SegTree {
    int n;


    SegTree() = default;
    SegTree(int size) : n(size), s(size * 4, 0) {}

    void assign(const vector<ll> &nums) {
        s.assign(nums.size() * 4, 0);
        _build(nums, 0, 0, nums.size());
    }

    void modify(int x, ll val) {
        _modify(x, val, 0, 0, n);
    }

    ll query_sum(int l, int r) const {
        return _query(l, r, 0, 0, n);
    }

private:
    vector<ll> s;
    void _build(const vector<ll> &nums, int i, int l, int r) {
        if (r - l == 1) {
            s[i] = nums[l];
            return;
        }
        int mid = (l + r) / 2;
        _build(nums, i * 2 + 1, l, mid);
        _build(nums, i * 2 + 2, mid, r);
        s[i] = s[i * 2 + 1] + s[i * 2 + 2];
    }

    void _modify(int x, ll val, int i, int l, int r) {
        if (r - l == 1) {
            s[i] = val;
            return;
        }
        int mid = (l + r) / 2;
        if (x < mid) {
            _modify(x, val, i * 2 + 1, l, mid);
        } else {
            _modify(x, val, i * 2 + 2, mid, r);
        }
        s[i] = s[i * 2 + 1] + s[i * 2 + 2];
    }

    ll _query(int ql, int qr, int i, int l, int r) const {
        if (ql <= l && qr >= r) {
            return s[i];
        }
        int mid = (l + r) / 2;
        ll ans = 0;
        if (ql < mid) {
            ans += _query(ql, qr, i * 2 + 1, l, mid);
        }
        if (qr > mid) {
            ans += _query(ql, qr, i * 2 + 2, mid, r);
        }
        return ans;
    }
};
struct Node {
	ll w;
	vector<int> e;
};
struct HLD {
	HLD(const vector<Node> &g, int r = 0)
		: nodes(g.size()), nfd(g.size()) {
		dfs1(g, r, -1);
		int now_index = 0;
		dfs2(g, r, -1, now_index, r);
		vector<ll> nums(g.size());
		for(int i = 0; i < g.size(); ++i) {
			nums[nodes[i].dfn] = g[i].w;
		}
		seg.assign(nums);
	}
	int lca(int u, int v) const {
		while(nodes[u].toc != nodes[v].toc) {
			if(nodes[nodes[u].toc].d < nodes[nodes[v].toc].d) {
				v = nodes[nodes[v].toc].fa;
			} else {
				u = nodes[nodes[u].toc].fa;
			}
		}
		return nodes[u].d < nodes[v].d ? u : v;
	}
	void modify(int x, ll v) {
		seg.modify(nodes[x].dfn, v);
	}
	ll query_sum(int u, int v) const {
		int lca_node = lca(u, v);
		auto query_to_lca = [&](int point) -> ll {
			ll ans = 0;
			for(; nodes[point].toc != nodes[lca_node].toc;
				point = nodes[nodes[point].toc].fa) {
				int pos1 = nodes[point].dfn;
				int pos2 = nodes[nodes[point].toc].dfn;
				ans += seg.query_sum(pos2, pos1 + 1);
			}
			int pos1 = nodes[lca_node].dfn;
			int pos2 = nodes[point].dfn;
			ans += seg.query_sum(pos1 + 1, pos2 + 1);
			return ans;
		};
		ll ans = query_to_lca(u);
		ans += query_to_lca(v);
		int lca_pos = nodes[lca_node].dfn;
		ans += seg.query_sum(lca_pos, lca_pos + 1);
		return ans;
	}
private:
	struct _Node {
		int d;
		int fa;
		int toc;
		int dfn;
		int sz;
		int hs;
	};
	void dfs1(const vector<Node> &g, int x, int fa) {
		if(fa == -1) {
			nodes[x].d = 0;
		} else {
			nodes[x].d = nodes[fa].d + 1;
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
	SegTree seg;
};