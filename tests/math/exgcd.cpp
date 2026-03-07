#include "exgcd.h"
#include "../test.h"

TEST(exgcd_basic) {
	auto [g, x, y] = exgcd(6, 4);
	ENSURE(g == 2);
	ENSURE(6 * x + 4 * y == 2);
}

TEST(exgcd_coprime) {
	auto [g, x, y] = exgcd(35, 15);
	ENSURE(g == 5);
	ENSURE(35 * x + 15 * y == 5);
}

TEST(exgcd_one) {
	auto [g, x, y] = exgcd(1, 1);
	ENSURE(g == 1);
	ENSURE(1 * x + 1 * y == 1);
}

TEST(exgcd_large) {
	auto [g, x, y] = exgcd(100, 75);
	ENSURE(g == 25);
	ENSURE(100 * x + 75 * y == 25);
}

TEST(exgcd_with_zero) {
	auto [g, x, y] = exgcd(5, 0);
	ENSURE(g == 5);
	ENSURE(5 * x + 0 * y == 5);
}

TEST(exgcd_prime_pair) {
	auto [g, x, y] = exgcd(17, 13);
	ENSURE(g == 1);
	ENSURE(17 * x + 13 * y == 1);
}
