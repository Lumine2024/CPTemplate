#include "math/modint.h"
#include "math/powtable.h"
#include "doctest.h"

namespace {
struct MulOnly {
	ll val;

	friend MulOnly operator*(MulOnly a, MulOnly b) {
		return {a.val * b.val};
	}
	friend bool operator==(MulOnly a, MulOnly b) = default;
};
} // namespace

constexpr unsigned mod = 998244353;
using Z = ModInt<mod>;

TEST_CASE("powtable_positive_exponent_without_inverse") {
	PowTable<MulOnly> table(MulOnly{3});
	REQUIRE(table.qpow(MulOnly{3}, 0, MulOnly{7}) == MulOnly{7});
	REQUIRE(table.qpow(MulOnly{3}, 5, MulOnly{2}) == MulOnly{486});
}

TEST_CASE("powtable_positive_exponent_with_inverse") {
	PowTable<Z> table(Z(3));
	REQUIRE(table.qpow(Z(3), 0, Z(7)) == Z(7));
	REQUIRE(table.qpow(Z(3), 5, Z(2)) == Z(486));
}

TEST_CASE("powtable_negative_exponent_with_inverse") {
	PowTable<Z> table(Z(3));
	Z inv3 = Z(3).inv();
	Z expect = Z(2);
	for(int i = 0; i < 4; ++i) {
		expect *= inv3;
	}
	REQUIRE(table.qpow(Z(3), -4, Z(2)) == expect);
}
