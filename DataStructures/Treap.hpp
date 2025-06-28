#pragma once
#include <bits/stdc++.h>
#include "Constants.hpp"
using namespace std;
using ll = long long;
using ull = unsigned long long;

struct Treap {
	Treap() : rt(nullptr) {}
	~Treap() {
		if(rt) {
			_dtor(rt);
		}
	}
	void insert(int v) {
		auto tmp = _sval(rt, v);
		auto l = _sval(tmp.first, v - 1);
		Node *node = l.second;
		if(!l.second) {
			node = new Node(v);
		} else {
			l.second->cnt++;
			l.second->usize();
		}
		Node *lc = _merge(l.first, node);
		rt = _merge(lc, tmp.second);
	}
	void erase(int v) {
		auto tmp = _sval(rt, v);
		auto l = _sval(tmp.first, v - 1);
		if(l.second->cnt > 1) {
			l.second->cnt--;
			l.second->usize();
			l.first = _merge(l.first, l.second);
		} else {
			if(tmp.first == l.second) {
				tmp.first = nullptr;
			}
			delete l.second;
			l.second = nullptr;
		}
		rt = _merge(l.first, tmp.second);
	}
	// 注意0-based
	int qrv(int v) const {
		return _qrv(rt, v);
	}
	// 注意0-based
	int qvr(int r) const {
		return _qvr(rt, r);
	}
	// 注意是小于的，不是大于等于的
	int lower_bound(int v) const {
		auto tmp = _sval(rt, v - 1);
		int ret = -inf;
		if(tmp.first) {
			ret = _qvr(tmp.first, tmp.first->size - 1);
		}
		rt = _merge(tmp.first, tmp.second);
		return ret;
	}
	int upper_bound(int v) const {
		auto tmp = _sval(rt, v);
		int ret = -inf;
		if(tmp.second) {
			ret = _qvr(tmp.second, 0);
		}
		rt = _merge(tmp.first, tmp.second);
		return ret;
	}
private:
	struct Node {
		int val;
		int cnt;
		int size;
		int prio;
		Node *left, *right;
		static inline random_device rnd{};
		Node(int v)
			: val(v), cnt(1), size(1), prio(rnd()), left(nullptr), right(nullptr) {}
		void usize() {
			size = cnt;
			if(left) {
				size += left->size;
			}
			if(right) {
				size += right->size;
			}
		}
	};
	mutable Node *rt;
	static void _dtor(Node *ptr) {
		if(ptr->left) {
			_dtor(ptr->left);
			ptr->left = nullptr;
		}
		if(ptr->right) {
			_dtor(ptr->right);
			ptr->right = nullptr;
		}
		delete ptr;
	}
	static pair<Node *, Node *> _sval(Node *const ptr, int key) {
		if(!ptr) {
			return { nullptr, nullptr };
		}
		if(ptr->val <= key) {
			auto tmp = _sval(ptr->right, key);
			ptr->right = tmp.first;
			ptr->usize();
			return { ptr, tmp.second };
		} else {
			auto tmp = _sval(ptr->left, key);
			ptr->left = tmp.second;
			ptr->usize();
			return { tmp.first, ptr };
		}
	}
	static tuple<Node *, Node *, Node *> _srnk(Node *const ptr, int rnk) {
		if(!ptr) return { nullptr, nullptr, nullptr };
		int lsize = (ptr->left ? ptr->left->size : 0);
		if(rnk < lsize) {
			auto [lptr, mptr, rptr] = _srnk(ptr->left, rnk);
			ptr->left = rptr;
			ptr->usize();
			return { lptr, mptr, ptr };
		} else if(rnk < lsize + ptr->cnt) {
			Node *lptr = ptr->left;
			Node *rptr = ptr->right;
			ptr->left = ptr->right = nullptr;
			return { lptr, ptr, rptr };
		} else {
			auto [lptr, mptr, rptr] = _srnk(ptr->right, rnk - lsize - ptr->cnt);
			ptr->right = lptr;
			ptr->usize();
			return { ptr, mptr, rptr };
		}
	}
	static Node *_merge(Node *const u, Node *const v) {
		if(!u) return v;
		if(!v) return u;
		if(u->prio < v->prio) {
			u->right = _merge(u->right, v);
			u->usize();
			return u;
		} else {
			v->left = _merge(u, v->left);
			v->usize();
			return v;
		}
	}
	int _qrv(Node *const ptr, int val) const {
		auto [l, r] = _sval(ptr, val - 1);
		int ret = (l ? l->size : 0);
		rt = _merge(l, r);
		return ret;
	}
	int _qvr(Node *const ptr, int r) const {
		auto [lptr, mptr, rptr] = _srnk(ptr, r);
		int ret = mptr->val;
		rt = _merge(_merge(lptr, mptr), rptr);
		return ret;
	}
};