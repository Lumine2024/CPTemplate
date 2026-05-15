#pragma once
#include "common.h"

template<class Info, class Tag>
concept TreapInfoTag = requires(Info a, Info b, Tag c, Tag d, vector<Info> vi,
								vector<Tag> vt, int u) {
	Info{};
	Tag{};
	{ a + b } -> same_as<Info>;
	{ c.apply(a, u) } -> same_as<void>;
	{ c.apply(d, u) } -> same_as<void>;
	{ c.empty() } -> same_as<bool>;
	{ c.clear() } -> same_as<void>;
	{ c.need_swap() } -> same_as<bool>;
	{ vi[u] } -> same_as<Info &>;
	{ vt[u] } -> same_as<Tag &>;
};

template<class Info, class Tag>
	requires(TreapInfoTag<Info, Tag>)
struct ImpTreap {
	ImpTreap() = default;
	~ImpTreap() {
		_dt(root);
	}
	int size() const {
		return siz(root);
	}
	void push_back(const Info &info) {
		root = merge(root, new Node(info));
	}
	void insert(int pos, const Info &info) {
		auto [a, b] = split(root, pos);
		root = merge(a, merge(new Node(info), b));
	}
	void apply(int l, int r, const Tag &tag) {
		auto [a, b] = split(root, l);
		auto [c, d] = split(b, r - l);
		apply(c, tag);
		root = merge(a, merge(c, d));
	}
	Info query(int l, int r) {
		auto [a, b] = split(root, l);
		auto [c, d] = split(b, r - l);
		Info ret = c ? c->info : Info{};
		root = merge(a, merge(c, d));
		return ret;
	}

private:
	static inline mt19937 rng{
		chrono::steady_clock::now().time_since_epoch().count()};
	struct Node {
		Info self, info;
		Tag tag;
		int pri, siz;
		Node *l = nullptr, *r = nullptr;
		Node(const Info &v)
			: self(v), info(v), tag(), pri((int)rng()), siz(1) {}
	};
	Node *root = nullptr;
	static int siz(Node *p) {
		return p ? p->siz : 0;
	}
	static Info info(Node *p) {
		return p ? p->info : Info{};
	}
	static void pull(Node *p) {
		if(!p) return;
		p->siz = 1 + siz(p->l) + siz(p->r);
		p->info = info(p->l) + p->self + info(p->r);
	}
	static void apply(Node *p, const Tag &tag) {
		if(!p) return;
		if(tag.need_swap()) swap(p->l, p->r);
		tag.apply(p->self, 1);
		tag.apply(p->info, p->siz);
		tag.apply(p->tag, p->siz);
	}
	static void push(Node *p) {
		if(!p || p->tag.empty()) return;
		apply(p->l, p->tag);
		apply(p->r, p->tag);
		p->tag.clear();
	}
	static Node *merge(Node *l, Node *r) {
		if(!l) return r;
		if(!r) return l;
		if(l->pri > r->pri) {
			push(l);
			l->r = merge(l->r, r);
			pull(l);
			return l;
		}
		push(r);
		r->l = merge(l, r->l);
		pull(r);
		return r;
	}
	static pair<Node *, Node *> split(Node *p, int cnt_left) {
		if(!p) return {nullptr, nullptr};
		push(p);
		if(cnt_left <= siz(p->l)) {
			auto [a, b] = split(p->l, cnt_left);
			p->l = b;
			pull(p);
			return {a, p};
		}
		auto [a, b] = split(p->r, cnt_left - siz(p->l) - 1);
		p->r = a;
		pull(p);
		return {p, b};
	}
	static void _dt(Node *p) {
		if(!p) return;
		_dt(p->l);
		_dt(p->r);
		delete p;
	}
};
