#include "math/crt.h"
#include "doctest.h"

TEST_CASE("crt_basic") {
	// x ≡ 2 (mod 3), x ≡ 3 (mod 5)
	// Solution: x ≡ 8 (mod 15)
	auto [a, m] = crt<ll>({2, 3}, {3, 5});
	REQUIRE(m == 15);
	REQUIRE(a % 3 == 2);
	REQUIRE(a % 5 == 3);
}

TEST_CASE("crt_single") {
	auto [a, m] = crt<ll>({5}, {7});
	REQUIRE(a == 5);
	REQUIRE(m == 7);
}

TEST_CASE("crt_three_equations") {
	// x ≡ 0 (mod 2), x ≡ 0 (mod 3), x ≡ 1 (mod 5)
	auto [a, m] = crt<ll>({0, 0, 1}, {2, 3, 5});
	REQUIRE(m == 30);
	REQUIRE(a % 2 == 0);
	REQUIRE(a % 3 == 0);
	REQUIRE(a % 5 == 1);
}

TEST_CASE("excrt_basic") {
	// Same as CRT: x ≡ 2 (mod 3), x ≡ 3 (mod 5)
	auto [a, m] = excrt<ll>({2, 3}, {3, 5});
	REQUIRE(m == 15);
	REQUIRE(a % 3 == 2);
	REQUIRE(a % 5 == 3);
}

TEST_CASE("excrt_non_coprime_compatible") {
	// x ≡ 0 (mod 4), x ≡ 2 (mod 6)
	// gcd(4,6)=2, 2-0=2 divisible by 2: compatible
	auto [a, m] = excrt<ll>({0, 2}, {4, 6});
	REQUIRE(a != -1);
	REQUIRE(a % 4 == 0);
	REQUIRE(a % 6 == 2);
}

TEST_CASE("excrt_non_coprime_incompatible") {
	// x ≡ 0 (mod 4), x ≡ 1 (mod 6)
	// gcd(4,6)=2, 1-0=1 not divisible by 2: incompatible
	auto [a, m] = excrt<ll>({0, 1}, {4, 6});
	REQUIRE(a == -1);
}
