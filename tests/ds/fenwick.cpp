#include "fenwick.h"
#include "../test.h"

TEST(empty_fenwick_test) {
	Fenwick<ll> f(100000);
	ENSURE(f.query(100) == 0);
}