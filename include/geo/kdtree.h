#pragma once
#include "geo/basic.h"

struct TwoDTree {
	explicit TwoDTree(const vector<Point> &pts) : val(pts.size()) {
		int n = val.size();
		for(int i = 0; i < n; ++i) {
			val[i].pt = pts[i];
			val[i].ls = val[i].rs = -1;
		}
		auto pushup = [&](int p) {
			for(int i = 0; i < 2; ++i) {
				val[p].L[i] = val[p].U[i] = val[p].pt[i];
				if(val[p].ls != -1) {
					chkmin(val[p].L[i], val[val[p].ls].L[i]);
					chkmax(val[p].U[i], val[val[p].ls].U[i]);
				}
				if(val[p].rs != -1) {
					chkmin(val[p].L[i], val[val[p].rs].L[i]);
					chkmax(val[p].U[i], val[val[p].rs].U[i]);
				}
			}
		};
		auto build = [&](auto &&build, int l, int r, int k) -> int {
			if(l >= r) return -1;
			int mid = (l + r) / 2;
			nth_element(val.begin() + l, val.begin() + mid, val.begin() + r,
						[&](const Node &a, const Node &b) {
							return a.pt[k] < b.pt[k];
						});
			val[mid].ls = build(build, l, mid, 1 - k);
			val[mid].rs = build(build, mid + 1, r, 1 - k);
			pushup(mid);
			return mid;
		};
		rt = build(build, 0, n, 0);
	}
	template<class Comp>
	ld kth_cmp(int k) {
		k *= 2;
		priority_queue<ld, vector<ld>, Comp> pq;
		for(int i = 0; i < val.size(); ++i) {
			kth(rt, val[i].pt, pq, k, 0);
		}
		return sqrt(pq.top());
	}
	ld kth_nearest(int k) {
		return kth_cmp<less<>>(k);
	}
	ld kth_farthest(int k) {
		return kth_cmp<greater<>>(k);
	}
	template<class Comp>
	ld kth_cmp(const Point &p, int k) {
		k *= 2;
		priority_queue<ld, vector<ld>, Comp> pq;
		kth(rt, p, pq, k, 0);
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
	vector<Node> val;
	int rt;
	template<class Comp>
	ld cmpdist(const Point &p, const Node &node);
	template<class Comp>
	void kth(int p, const Point &q, priority_queue<ld, vector<ld>, Comp> &pq,
			 int k, int dep) {
		static Comp comp;
		if(p == -1) return;
		ld dist = (val[p].pt - q).len2();
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
		if(q[dim] < val[p].pt[dim]) {
			fi = val[p].rs;
			se = val[p].ls;
		} else {
			fi = val[p].ls;
			se = val[p].rs;
		}
		if(fi != -1) {
			kth(fi, q, pq, k, dep + 1);
		}
		if(se != -1) {
			ld md = cmpdist<Comp>(q, val[se]);
			if(comp(md, pq.size() < k ? inf : pq.top()) || pq.size() < k) {
				kth(se, q, pq, k, dep + 1);
			}
		}
	}
};

template<class Comp>
ld TwoDTree::cmpdist(const Point &p, const Node &node) = delete;
template<>
ld TwoDTree::cmpdist<less<>>(const Point &p, const Node &node) {
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
template<>
ld TwoDTree::cmpdist<greater<>>(const Point &p, const Node &node) {
	ld dx = max(abs(p.x - node.L[0]), abs(p.x - node.U[0]));
	ld dy = max(abs(p.y - node.L[1]), abs(p.y - node.U[1]));
	return dx * dx + dy * dy;
}
