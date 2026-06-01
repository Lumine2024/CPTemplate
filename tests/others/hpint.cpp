#include "others/hpint.h"
#include "doctest.h"

static void ensure_eq_str(const HPINT &x, const string &s) {
	REQUIRE(static_cast<string>(x) == s);
}

TEST_CASE("hpint_simple") {
	for(int i = 0; i < 100; ++i) {
		for(int j = 0; j < 100; ++j) {
			HPINT a = i, b = j;
			HPINT add_hp = a + b;
			HPINT add_int = i + j;
			REQUIRE(add_hp == add_int);
			HPINT sub_hp = a - b;
			HPINT sub_int = i - j;
			REQUIRE(sub_hp == sub_int);
			HPINT mul_hp = a * b;
			HPINT mul_int = i * j;
			REQUIRE(mul_hp == mul_int);
		}
	}
}

TEST_CASE("hpint_signed_small_range") {
	for(int i = -60; i <= 60; ++i) {
		for(int j = -60; j <= 60; ++j) {
			HPINT a = i, b = j;
			REQUIRE(a + b == HPINT(i + j));
			REQUIRE(a - b == HPINT(i - j));
			REQUIRE(a * b == HPINT(1ll * i * j));
		}
	}
}

TEST_CASE("hpint_large_add_sub_mul") {
	HPINT a = string("123456789012345678901234567890");
	HPINT b = string("987654321098765432109876543210");
	ensure_eq_str(a + b, "1111111110111111111011111111100");
	ensure_eq_str(b - a, "864197532086419753208641975320");
	ensure_eq_str(a - b, "-864197532086419753208641975320");

	HPINT c = string("123456789123456789");
	HPINT d = string("987654321987654321");
	ensure_eq_str(c * d, "121932631356500531347203169112635269");
}

TEST_CASE("hpint_compound_assign") {
	HPINT a = 1000;
	a += HPINT(-250);
	REQUIRE(a == HPINT(750));
	a -= HPINT(1750);
	REQUIRE(a == HPINT(-1000));
	a *= HPINT(-12);
	REQUIRE(a == HPINT(12000));
}

TEST_CASE("hpint_compare") {
	HPINT a = string("999999999999999999999");
	HPINT b = string("1000000000000000000000");
	HPINT c = -1;
	HPINT d = 0;
	REQUIRE(a < b);
	REQUIRE(b > a);
	REQUIRE(c < d);
	REQUIRE(a >= a);
	REQUIRE(a <= a);
}

TEST_CASE("hpint_stream_io") {
	stringstream ss("   -12345 xyz 67890");
	HPINT x, y;
	ss >> x >> y;
	ensure_eq_str(x, "-12345");
	ensure_eq_str(y, "67890");

	stringstream out;
	out << x << ' ' << y;
	REQUIRE(out.str() == "-12345 67890");
}