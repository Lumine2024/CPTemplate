#include "sparse.h"
#include "../test.h"

TEST(sparse_min_query) {
	vector<int> v = {5, 1, 3, 2, 4};
	Sparse<int> sp(v, [](int a, int b) { return min(a, b); });
	ENSURE(sp.query(0, 4) == 1);
	ENSURE(sp.query(0, 0) == 5);
	ENSURE(sp.query(2, 4) == 2);
	ENSURE(sp.query(1, 3) == 1);
}

TEST(sparse_max_query) {
	vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6};
	Sparse<int> sp(v, [](int a, int b) { return max(a, b); });
	ENSURE(sp.query(0, 7) == 9);
	ENSURE(sp.query(0, 4) == 5);
	ENSURE(sp.query(3, 5) == 9);
	ENSURE(sp.query(6, 7) == 6);
}

TEST(sparse_single_element) {
	vector<int> v = {42};
	Sparse<int> sp(v, [](int a, int b) { return min(a, b); });
	ENSURE(sp.query(0, 0) == 42);
}

TEST(sparse_sorted) {
	vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8};
	Sparse<int> sp(v, [](int a, int b) { return min(a, b); });
	for(int l = 0; l < 8; ++l) {
		for(int r = l; r < 8; ++r) {
			ENSURE(sp.query(l, r) == v[l]);
		}
	}
}

TEST(sparse_reverse_sorted) {
	vector<int> v = {8, 7, 6, 5, 4, 3, 2, 1};
	Sparse<int> sp(v, [](int a, int b) { return min(a, b); });
	for(int l = 0; l < 8; ++l) {
		for(int r = l; r < 8; ++r) {
			ENSURE(sp.query(l, r) == v[r]);
		}
	}
}
