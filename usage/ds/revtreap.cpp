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

constexpr int maxn = 100005, inf = 0x3f3f3f3f;

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
	void reverse(int l, int r) {
		auto [a, b] = _srev(rt, l);
		auto [c, d] = _srev(b, r - l);
		if(c) c->rev ^= true;
		rt = _mrev(a, _mrev(c, d));
	}
	vector<int> inorder() const {
		vector<int> ret;
		ret.reserve(rt->size);
		auto dfs = [&](auto &&dfs, Node *ptr) -> void {
			if(!ptr) return;
			ptr->urev();
			dfs(dfs, ptr->left);
			ret.push_back(ptr->val);
			dfs(dfs, ptr->right);
		};
		dfs(dfs, rt);
		return ret;
	}

private:
	struct Node {
		int val, cnt, size, prio;
		Node *left, *right;
		bool rev;
		static inline random_device rnd{};
		Node(int v)
			: val(v), cnt(1), size(1), prio(rnd()), left(nullptr),
			  right(nullptr), rev(false) {}
		void usize() {
			size = cnt;
			if(left) size += left->size;
			if(right) size += right->size;
		}
		void urev() {
			if(rev) {
				swap(left, right);
				if(left != nullptr) left->rev ^= true;
				if(right != nullptr) right->rev ^= true;
				rev = false;
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
		if(!ptr) return {nullptr, nullptr};
		if(ptr->val <= key) {
			auto tmp = _sval(ptr->right, key);
			ptr->right = tmp.first;
			ptr->usize();
			return {ptr, tmp.second};
		} else {
			auto tmp = _sval(ptr->left, key);
			ptr->left = tmp.second;
			ptr->usize();
			return {tmp.first, ptr};
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
	static pair<Node *, Node *> _srev(Node *const ptr, int k) {
		if(!ptr) return {nullptr, nullptr};
		ptr->urev();
		if(k == 0 || (ptr->left && ptr->left->size >= k)) {
			auto [pf, ps] = _srev(ptr->left, k);
			ptr->left = ps;
			ptr->usize();
			return {pf, ptr};
		} else {
			auto [pf, ps] =
				_srev(ptr->right, k - 1 - (ptr->left ? ptr->left->size : 0));
			ptr->right = pf;
			ptr->usize();
			return {ptr, ps};
		}
	}
	static Node *_mrev(Node *const a, Node *const b) {
		if(!a) return b;
		if(!b) return a;
		if(a->prio < b->prio) {
			a->urev();
			a->right = _mrev(a->right, b);
			a->usize();
			return a;
		} else {
			b->urev();
			b->left = _mrev(a, b->left);
			b->usize();
			return b;
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
