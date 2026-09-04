#pragma once
#include "common.h"

template<class T, class Cmp = less<T>, class Eq = equal_to<T>>
struct DelHeap {
	DelHeap() = default;
	int size() {
		clear();
		return pq.size() - del.size();
	}
	bool empty() {
		return size() == 0;
	}
	void clear() {
		while(!pq.empty() && !del.empty() && eqf(pq.top(), del.top())) {
			pq.pop();
			del.pop();
		}
	}
	void push(T x) {
		clear();
		pq.push(x);
	}
	// 请保证 x 在这个堆里，否则可删堆会失效
	void pop(T x) {
		del.push(x);
		clear();
	}
	T top() {
		clear();
		assert(!pq.empty());
		return pq.top();
	}

private:
	priority_queue<T, vector<T>, Cmp> pq, del;
	Eq eqf;
};
