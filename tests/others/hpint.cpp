#include "hpint.h"
#include "../test.h"

static void ensure_eq_str(const HPINT &x, const string &s) {
	ENSURE(static_cast<string>(x) == s);
}

TEST(hpint_simple) {
	for(int i = 0; i < 100; ++i) {
		for(int j = 0; j < 100; ++j) {
			HPINT a = i, b = j;
			HPINT add_hp = a + b;
			HPINT add_int = i + j;
			ENSURE(add_hp == add_int);
			HPINT sub_hp = a - b;
			HPINT sub_int = i - j;
			ENSURE(sub_hp == sub_int);
			HPINT mul_hp = a * b;
			HPINT mul_int = i * j;
			ENSURE(mul_hp == mul_int);
		}
	}
}

TEST(hpint_signed_small_range) {
	for(int i = -60; i <= 60; ++i) {
		for(int j = -60; j <= 60; ++j) {
			HPINT a = i, b = j;
			ENSURE(a + b == HPINT(i + j));
			ENSURE(a - b == HPINT(i - j));
			ENSURE(a * b == HPINT(1ll * i * j));
		}
	}
}

TEST(hpint_large_add_sub_mul) {
	HPINT a = string("123456789012345678901234567890");
	HPINT b = string("987654321098765432109876543210");
	ensure_eq_str(a + b, "1111111110111111111011111111100");
	ensure_eq_str(b - a, "864197532086419753208641975320");
	ensure_eq_str(a - b, "-864197532086419753208641975320");

	HPINT c = string("123456789123456789");
	HPINT d = string("987654321987654321");
	ensure_eq_str(c * d, "121932631356500531347203169112635269");
}

TEST(hpint_compound_assign) {
	HPINT a = 1000;
	a += HPINT(-250);
	ENSURE(a == HPINT(750));
	a -= HPINT(1750);
	ENSURE(a == HPINT(-1000));
	a *= HPINT(-12);
	ENSURE(a == HPINT(12000));
}

TEST(hpint_compare) {
	HPINT a = string("999999999999999999999");
	HPINT b = string("1000000000000000000000");
	HPINT c = -1;
	HPINT d = 0;
	ENSURE(a < b);
	ENSURE(b > a);
	ENSURE(c < d);
	ENSURE(a >= a);
	ENSURE(a <= a);
}

TEST(hpint_stream_io) {
	stringstream ss("   -12345 xyz 67890");
	HPINT x, y;
	ss >> x >> y;
	ensure_eq_str(x, "-12345");
	ensure_eq_str(y, "67890");

	stringstream out;
	out << x << ' ' << y;
	ENSURE(out.str() == "-12345 67890");
}