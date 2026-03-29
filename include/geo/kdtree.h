#pragma once
#include "basic.h"

struct TwoDTree {
	explicit TwoDTree(const vector<Point> &pts) : nodes(pts.size()) {
		int n = nodes.size();
		for(int i = 0; i < n; ++i) {
			nodes[i].pt = pts[i];
			nodes[i].ls = nodes[i].rs = -1;
		}
		auto pushup = [&](int p) {
			for(int i = 0; i < 2; ++i) {
				nodes[p].L[i] = nodes[p].U[i] = nodes[p].pt[i];
				if(nodes[p].ls != -1) {
					chkmin(nodes[p].L[i], nodes[nodes[p].ls].L[i]);
					chkmax(nodes[p].U[i], nodes[nodes[p].ls].U[i]);
				}
				if(nodes[p].rs != -1) {
					chkmin(nodes[p].L[i], nodes[nodes[p].rs].L[i]);
					chkmax(nodes[p].U[i], nodes[nodes[p].rs].U[i]);
				}
			}
		};
		auto build = [&](auto &&build, int l, int r, int k) -> int {
			if(l >= r) return -1;
			int mid = (l + r) / 2;
			nth_element(nodes.begin() + l, nodes.begin() + mid,
						nodes.begin() + r, [&](const Node &a, const Node &b) {
							return a.pt[k] < b.pt[k];
						});
			nodes[mid].ls = build(build, l, mid, 1 - k);
			nodes[mid].rs = build(build, mid + 1, r, 1 - k);
			pushup(mid);
			return mid;
		};
		root = build(build, 0, n, 0);
	}
	template<class Comp> ld kth_cmp(int k) {
		k *= 2;
		priority_queue<ld, vector<ld>, Comp> pq;
		for(int i = 0; i < nodes.size(); ++i) {
			kth(root, nodes[i].pt, pq, k, 0);
		}
		return sqrt(pq.top());
	}
	ld kth_nearest(int k) {
		return kth_cmp<less<>>(k);
	}
	ld kth_farthest(int k) {
		return kth_cmp<greater<>>(k);
	}
	template<class Comp> ld kth_cmp(const Point &p, int k) {
		k *= 2;
		priority_queue<ld, vector<ld>, Comp> pq;
		kth(root, p, pq, k, 0);
		return sqrt(pq.top());
	}
	ld kth_nearest(const Point &p, int k) {
		return kth_cmp<less<>>(p, k);
	}
	ld kth_farthest(const Point &p, int k) {
		return kth_cmp<greater<>>(p, k);
	}

private:
	struct Node {
		int ls, rs;
		Point pt;
		ld L[2], U[2];
	};
	vector<Node> nodes;
	int root;
	template<class Comp> ld cmpdist(const Point &p, const Node &node);
	template<class Comp>
	void kth(int p, const Point &q, priority_queue<ld, vector<ld>, Comp> &pq,
			 int k, int dep) {
		static Comp comp;
		if(p == -1) return;
		ld dist = (nodes[p].pt - q).len2();
		if(dist > 1e-12) {
			if(pq.size() < k) {
				pq.push(dist);
			} else if(comp(dist, pq.top())) {
				pq.pop();
				pq.push(dist);
			}
		}
		int dim = dep % 2;
		int fi, se;
		if(q[dim] < nodes[p].pt[dim]) {
			fi = nodes[p].rs;
			se = nodes[p].ls;
		} else {
			fi = nodes[p].ls;
			se = nodes[p].rs;
		}
		if(fi != -1) {
			kth(fi, q, pq, k, dep + 1);
		}
		if(se != -1) {
			ld md = cmpdist<Comp>(q, nodes[se]);
			if(comp(md, pq.size() < k ? inf : pq.top()) || pq.size() < k) {
				kth(se, q, pq, k, dep + 1);
			}
		}
	}
};

template<class Comp>
ld TwoDTree::cmpdist(const Point &p, const Node &node) = delete;
template<> ld TwoDTree::cmpdist<less<>>(const Point &p, const Node &node) {
	ld d = 0;
	for(int i = 0; i < 2; ++i) {
		if(p[i] < node.L[i]) {
			ld t = node.L[i] - p[i];
			d += t * t;
		} else if(p[i] > node.U[i]) {
			ld t = p[i] - node.U[i];
			d += t * t;
		}
	}
	return d;
}
template<> ld TwoDTree::cmpdist<greater<>>(const Point &p, const Node &node) {
	ld dx = max(abs(p.x - node.L[0]), abs(p.x - node.U[0]));
	ld dy = max(abs(p.y - node.L[1]), abs(p.y - node.U[1]));
	return dx * dx + dy * dy;
}
