#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

// persistent segment tree
struct PST {
	const int n;
	PST(int n_) : n(n_) {
		nodes.reserve(2 * n * (int)log2(n));
		vers.reserve(n + 1);
		vers.push_back(_build(0, n - 1));
	}
	void update(int k) {
		vers.push_back(_update(k, vers.back(), 0, n - 1));
	}
	// 这里为解决静态区间第k小问题设计，传入k, l, r
	int query(int k, int ver1, int ver2) const {
		return _query(k, vers[ver1 - 1], vers[ver2], 0, n - 1);
	}
private:
	struct Node {
		int l, r;
		int cnt;
	};
	vector<Node> nodes;
	vector<int> vers;
	int _build(int l, int r) {
		int ret = nodes.size();
		if(l == r) {
			nodes.emplace_back(-1, -1, 0);
			return ret;
		}
		nodes.emplace_back(-1, -1, 0);
		int mid = (l + r) >> 1;
		nodes[ret].l = _build(l, mid);
		nodes[ret].r = _build(mid + 1, r);
		return ret;
	}
	int _update(int k, int root, int l, int r) {
		int ret = nodes.size();
		nodes.emplace_back(nodes[root]);
		nodes[ret].cnt++;
		if(l == r) {
			return ret;
		}
		int mid = (l + r) >> 1;
		if(k <= mid) {
			nodes[ret].l = _update(k, nodes[root].l, l, mid);
		} else {
			nodes[ret].r = _update(k, nodes[root].r, mid + 1, r);
		}
		return ret;
	}
	int _query(int k, int root1, int root2, int l, int r) const {
		if(l == r) return l;
		int mid = (l + r) >> 1;
		int cntl = nodes[nodes[root2].l].cnt - nodes[nodes[root1].l].cnt;
		if(k <= cntl) {
			return _query(k, nodes[root1].l, nodes[root2].l, l, mid);
		} else {
			return _query(k - cntl, nodes[root1].r, nodes[root2].r, mid + 1, r);
		}
	}
};
/*
struct PST {
	PST() : node_cnt(0), len(0) {}
	PST(const vector<ll> &a) {
		build(a);
	}
	void build(const vector<ll> &a) {
		ys = a;
		ind = a;
		sort(ind.begin(), ind.end());
		ind.erase(unique(ind.begin(), ind.end()), ind.end());
		len = ind.size();
		node_cnt = 0;
		ll n = a.size();
		sum.assign(n * 50, 0);
		lson.assign(n * 50, 0);
		rson.assign(n * 50, 0);
		roots.assign(n + 1, 0);
		roots[0] = _build(0, len - 1);
		for(ll i = 1; i <= n; i++) {
			roots[i] = _update(_getid(a[i - 1]), 0, len - 1, roots[i - 1]);
		}
	}
	// 查询区间第k小
	ll qmink(int L, int R, int k) {
		return ind[_query(0, len - 1, roots[L - 1], roots[R], k)];
	}
	// 查询区间第k大
	ll qmaxk(int L, int R, int k) {
		int n = R - L + 1;
		return qmink(L, R, n - k + 1);
	}
	// 查询前缀[1,pos]中小于x的元素个数
	ll qltx(int pos, ll x) {
		int idx = _getid(x + 1) - 1; // 离散化位置
		if(roots[pos] == 0 || idx < 0) return 0;
		return _getcnt(roots[pos], 0, len - 1, idx);
	}
	// 查询区间[L,R]中值在[l_val, r_val]的元素个数
	ll qcnt(int L, int R, ll l_val, ll r_val) {
		ll r_high = qltx(R, r_val);
		ll r_low = qltx(R, l_val - 1);
		ll l_high = qltx(L - 1, r_val);
		ll l_low = qltx(L - 1, l_val - 1);
		return (r_high - r_low) - (l_high - l_low);
	}

private:
	vector<ll> ind;		// 离散化数组
	vector<ll> ys;		// 原始数组
	vector<ll> sum;		// 节点计数
	vector<ll> lson;	// 左子节点索引
	vector<ll> rson;	// 右子节点索引
	vector<ll> roots;	// 各版本根节点
	ll len;				// 离散值域大小
	ll node_cnt;		// 节点总数
	// 获取离散化下标
	ll _getid(ll x) {
		return lower_bound(ind.begin(), ind.end(), x) - ind.begin();
	}
	// 构建空树
	ll _build(ll l, ll r) {
		ll id = ++node_cnt;
		if(l == r) return id;
		ll mid = (l + r) >> 1;
		lson[id] = _build(l, mid);
		rson[id] = _build(mid + 1, r);
		return id;
	}
	// 更新树版本
	ll _update(ll pos, ll l, ll r, ll pre) {
		ll id = ++node_cnt;
		lson[id] = lson[pre];
		rson[id] = rson[pre];
		sum[id] = sum[pre] + 1;
		if(l == r) return id;
		ll mid = (l + r) >> 1;
		if(pos <= mid)
			lson[id] = _update(pos, l, mid, lson[pre]);
		else
			rson[id] = _update(pos, mid + 1, r, rson[pre]);
		return id;
	}

	// 查询第k小
	ll _query(ll l, ll r, ll L_id, ll R_id, ll k) {
		if(l == r) return l;
		ll mid = (l + r) >> 1;
		ll left_count = sum[lson[R_id]] - sum[lson[L_id]];
		if(left_count >= k)
			return _query(l, mid, lson[L_id], lson[R_id], k);
		else
			return _query(mid + 1, r, rson[L_id], rson[R_id], k - left_count);
	}

	// 计算值<=x的元素个数
	ll _getcnt(ll id, ll l, ll r, ll x) {
		if(l == r) return sum[id];
		ll mid = (l + r) >> 1;
		if(x <= mid)
			return _getcnt(lson[id], l, mid, x);
		else
			return sum[lson[id]] + _getcnt(rson[id], mid + 1, r, x);
	}
};
*/