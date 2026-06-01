#include "math/exgcd.h"
#include "doctest.h"

TEST_CASE("exgcd_basic") {
	auto [g, x, y] = exgcd(6, 4);
	REQUIRE(g == 2);
	REQUIRE(6 * x + 4 * y == 2);
}

TEST_CASE("exgcd_coprime") {
	auto [g, x, y] = exgcd(35, 15);
	REQUIRE(g == 5);
	REQUIRE(35 * x + 15 * y == 5);
}

TEST_CASE("exgcd_one") {
	auto [g, x, y] = exgcd(1, 1);
	REQUIRE(g == 1);
	REQUIRE(1 * x + 1 * y == 1);
}

TEST_CASE("exgcd_large") {
	auto [g, x, y] = exgcd(100, 75);
	REQUIRE(g == 25);
	REQUIRE(100 * x + 75 * y == 25);
}

TEST_CASE("exgcd_with_zero") {
	auto [g, x, y] = exgcd(5, 0);
	REQUIRE(g == 5);
	REQUIRE(5 * x + 0 * y == 5);
}

TEST_CASE("exgcd_prime_pair") {
	auto [g, x, y] = exgcd(17, 13);
	REQUIRE(g == 1);
	REQUIRE(17 * x + 13 * y == 1);
}
