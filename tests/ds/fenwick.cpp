#include "ds/fenwick.h"
#include "doctest.h"

TEST_CASE("empty_fenwick_test") {
	Fenwick<ll> f(100000);
	REQUIRE(f.query(100) == 0);
}

TEST_CASE("fenwick_prefix_sum") {
	Fenwick<ll> f(5);
	for(int i = 1; i <= 5; ++i) f.update(i, i);
	// prefix sums: 1, 3, 6, 10, 15
	REQUIRE(f.query(1) == 1);
	REQUIRE(f.query(3) == 6);
	REQUIRE(f.query(5) == 15);
}

TEST_CASE("fenwick_point_update") {
	Fenwick<ll> f(5);
	f.update(3, 10);
	REQUIRE(f.query(2) == 0);
	REQUIRE(f.query(3) == 10);
	REQUIRE(f.query(5) == 10);
	f.update(3, -3);
	REQUIRE(f.query(3) == 7);
}

TEST_CASE("range_fenwick_basic") {
	RangeFenwick<ll> rf(5);
	// Add 2 to range [1, 4) = positions 1, 2, 3
	rf.update(1, 4, 2);
	REQUIRE(rf.query(1) == 2);
	REQUIRE(rf.query(2) == 4);
	REQUIRE(rf.query(3) == 6);
	REQUIRE(rf.query(4) == 6);
	REQUIRE(rf.query(5) == 6);
}

TEST_CASE("range_fenwick_multiple_updates") {
	RangeFenwick<ll> rf(5);
	// [1,3): +1 at positions 1,2; [2,4): +2 at positions 2,3
	rf.update(1, 3, 1);
	rf.update(2, 4, 2);
	// Values: a[1]=1, a[2]=3, a[3]=2, a[4]=0, a[5]=0
	// prefix sums: 1, 4, 6, 6, 6
	REQUIRE(rf.query(1) == 1);
	REQUIRE(rf.query(2) == 4);
	REQUIRE(rf.query(3) == 6);
	REQUIRE(rf.query(4) == 6);
	REQUIRE(rf.query(5) == 6);
}

void check_fenwick_values(const Fenwick<ll> &f) {
	REQUIRE(f.query(1) == 1);
	REQUIRE(f.query(3) == 6);
	REQUIRE(f.query(5) == 15);
}

TEST_CASE("ensure_in_helper_function") {
	Fenwick<ll> f(5);
	for(int i = 1; i <= 5; ++i) f.update(i, i);
	check_fenwick_values(f);
}

TEST_CASE("ensure_in_lambda") {
	Fenwick<ll> f(5);
	for(int i = 1; i <= 5; ++i) f.update(i, i);
	auto check = [&]() {
		REQUIRE(f.query(1) == 1);
		REQUIRE(f.query(3) == 6);
		REQUIRE(f.query(5) == 15);
	};
	check();
}