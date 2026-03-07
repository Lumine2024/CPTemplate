#include "fenwick.h"
#include "../test.h"

TEST(empty_fenwick_test) {
	Fenwick<ll> f(100000);
	ENSURE(f.query(100) == 0);
}

TEST(fenwick_prefix_sum) {
	Fenwick<ll> f(5);
	for(int i = 1; i <= 5; ++i) f.update(i, i);
	// prefix sums: 1, 3, 6, 10, 15
	ENSURE(f.query(1) == 1);
	ENSURE(f.query(3) == 6);
	ENSURE(f.query(5) == 15);
}

TEST(fenwick_point_update) {
	Fenwick<ll> f(5);
	f.update(3, 10);
	ENSURE(f.query(2) == 0);
	ENSURE(f.query(3) == 10);
	ENSURE(f.query(5) == 10);
	f.update(3, -3);
	ENSURE(f.query(3) == 7);
}

TEST(range_fenwick_basic) {
	RangeFenwick<ll> rf(5);
	// Add 2 to range [1, 4) = positions 1, 2, 3
	rf.update(1, 4, 2);
	ENSURE(rf.query(1) == 2);
	ENSURE(rf.query(2) == 4);
	ENSURE(rf.query(3) == 6);
	ENSURE(rf.query(4) == 6);
	ENSURE(rf.query(5) == 6);
}

TEST(range_fenwick_multiple_updates) {
	RangeFenwick<ll> rf(5);
	// [1,3): +1 at positions 1,2; [2,4): +2 at positions 2,3
	rf.update(1, 3, 1);
	rf.update(2, 4, 2);
	// Values: a[1]=1, a[2]=3, a[3]=2, a[4]=0, a[5]=0
	// prefix sums: 1, 4, 6, 6, 6
	ENSURE(rf.query(1) == 1);
	ENSURE(rf.query(2) == 4);
	ENSURE(rf.query(3) == 6);
	ENSURE(rf.query(4) == 6);
	ENSURE(rf.query(5) == 6);
}