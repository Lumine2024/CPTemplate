#include "dsu.h"
#include "../test.h"

TEST(dsu_basic) {
	DSU dsu(5);
	// Initially all nodes are isolated
	ENSURE(!dsu.is_connected(0, 1));
	ENSURE(!dsu.is_connected(1, 2));
	ENSURE(dsu.size(0) == 1);
	ENSURE(dsu.size(1) == 1);
}

TEST(dsu_connect_and_query) {
	DSU dsu(5);
	dsu.connect(0, 1);
	ENSURE(dsu.is_connected(0, 1));
	ENSURE(!dsu.is_connected(0, 2));
	ENSURE(dsu.size(0) == 2);
	ENSURE(dsu.size(1) == 2);

	dsu.connect(1, 2);
	ENSURE(dsu.is_connected(0, 2));
	ENSURE(dsu.size(0) == 3);
}

TEST(dsu_transitivity) {
	DSU dsu(6);
	dsu.connect(0, 1);
	dsu.connect(2, 3);
	dsu.connect(4, 5);
	ENSURE(!dsu.is_connected(0, 2));
	ENSURE(!dsu.is_connected(1, 3));
	dsu.connect(1, 2);
	ENSURE(dsu.is_connected(0, 3));
	ENSURE(dsu.is_connected(1, 3));
	ENSURE(!dsu.is_connected(0, 4));
	ENSURE(dsu.size(0) == 4);
}

TEST(dsu_self_connect) {
	DSU dsu(3);
	dsu.connect(0, 0);
	ENSURE(dsu.size(0) == 1);
	dsu.connect(1, 2);
	ENSURE(dsu.is_connected(1, 2));
	ENSURE(!dsu.is_connected(0, 1));
}

TEST(dsu_large) {
	int n = 1000;
	DSU dsu(n);
	for(int i = 0; i < n - 1; ++i) {
		dsu.connect(i, i + 1);
	}
	for(int i = 0; i < n; ++i) {
		ENSURE(dsu.is_connected(0, i));
	}
	ENSURE(dsu.size(0) == n);
}
