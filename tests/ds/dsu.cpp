#include "ds/dsu.h"
#include "doctest.h"

TEST_CASE("dsu_basic") {
	DSU dsu(5);
	// Initially all nodes are isolated
	REQUIRE(!dsu.is_connected(0, 1));
	REQUIRE(!dsu.is_connected(1, 2));
	REQUIRE(dsu.size(0) == 1);
	REQUIRE(dsu.size(1) == 1);
}

TEST_CASE("dsu_connect_and_query") {
	DSU dsu(5);
	dsu.connect(0, 1);
	REQUIRE(dsu.is_connected(0, 1));
	REQUIRE(!dsu.is_connected(0, 2));
	REQUIRE(dsu.size(0) == 2);
	REQUIRE(dsu.size(1) == 2);

	dsu.connect(1, 2);
	REQUIRE(dsu.is_connected(0, 2));
	REQUIRE(dsu.size(0) == 3);
}

TEST_CASE("dsu_transitivity") {
	DSU dsu(6);
	dsu.connect(0, 1);
	dsu.connect(2, 3);
	dsu.connect(4, 5);
	REQUIRE(!dsu.is_connected(0, 2));
	REQUIRE(!dsu.is_connected(1, 3));
	dsu.connect(1, 2);
	REQUIRE(dsu.is_connected(0, 3));
	REQUIRE(dsu.is_connected(1, 3));
	REQUIRE(!dsu.is_connected(0, 4));
	REQUIRE(dsu.size(0) == 4);
}

TEST_CASE("dsu_self_connect") {
	DSU dsu(3);
	dsu.connect(0, 0);
	REQUIRE(dsu.size(0) == 1);
	dsu.connect(1, 2);
	REQUIRE(dsu.is_connected(1, 2));
	REQUIRE(!dsu.is_connected(0, 1));
}

TEST_CASE("dsu_large") {
	int n = 1000;
	DSU dsu(n);
	for(int i = 0; i < n - 1; ++i) {
		dsu.connect(i, i + 1);
	}
	for(int i = 0; i < n; ++i) {
		REQUIRE(dsu.is_connected(0, i));
	}
	REQUIRE(dsu.size(0) == n);
}
