#include "sterlingntt.h"
#include "../test.h"

TEST(sterling_k0) {
	// S(0, 0) = 1
	auto v = sterling_ntt(0);
	ENSURE(v.size() == 1);
	ENSURE(v[0] == 1);
}

TEST(sterling_k1) {
	// S(1, 0) = 0, S(1, 1) = 1
	auto v = sterling_ntt(1);
	ENSURE(v.size() == 2);
	ENSURE(v[0] == 0);
	ENSURE(v[1] == 1);
}

TEST(sterling_k2) {
	// S(2, 1) = 1, S(2, 2) = 1
	auto v = sterling_ntt(2);
	ENSURE(v.size() == 3);
	ENSURE(v[0] == 0);
	ENSURE(v[1] == 1);
	ENSURE(v[2] == 1);
}

TEST(sterling_k3) {
	// S(3, 1) = 1, S(3, 2) = 3, S(3, 3) = 1
	auto v = sterling_ntt(3);
	ENSURE(v.size() == 4);
	ENSURE(v[0] == 0);
	ENSURE(v[1] == 1);
	ENSURE(v[2] == 3);
	ENSURE(v[3] == 1);
}

TEST(sterling_k4) {
	// S(4, 1)=1, S(4, 2)=7, S(4, 3)=6, S(4, 4)=1
	auto v = sterling_ntt(4);
	ENSURE(v.size() == 5);
	ENSURE(v[0] == 0);
	ENSURE(v[1] == 1);
	ENSURE(v[2] == 7);
	ENSURE(v[3] == 6);
	ENSURE(v[4] == 1);
}

TEST(sterling_k5) {
	// S(5, 1)=1, S(5, 2)=15, S(5, 3)=25, S(5, 4)=10, S(5, 5)=1
	auto v = sterling_ntt(5);
	ENSURE(v.size() == 6);
	ENSURE(v[1] == 1);
	ENSURE(v[2] == 15);
	ENSURE(v[3] == 25);
	ENSURE(v[4] == 10);
	ENSURE(v[5] == 1);
}
