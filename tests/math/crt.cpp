#include "math/crt.h"
#include "../test.h"

TEST(crt_basic) {
	// x ≡ 2 (mod 3), x ≡ 3 (mod 5)
	// Solution: x ≡ 8 (mod 15)
	auto [a, m] = crt<ll>({2, 3}, {3, 5});
	ENSURE(m == 15);
	ENSURE(a % 3 == 2);
	ENSURE(a % 5 == 3);
}

TEST(crt_single) {
	auto [a, m] = crt<ll>({5}, {7});
	ENSURE(a == 5);
	ENSURE(m == 7);
}

TEST(crt_three_equations) {
	// x ≡ 0 (mod 2), x ≡ 0 (mod 3), x ≡ 1 (mod 5)
	auto [a, m] = crt<ll>({0, 0, 1}, {2, 3, 5});
	ENSURE(m == 30);
	ENSURE(a % 2 == 0);
	ENSURE(a % 3 == 0);
	ENSURE(a % 5 == 1);
}

TEST(excrt_basic) {
	// Same as CRT: x ≡ 2 (mod 3), x ≡ 3 (mod 5)
	auto [a, m] = excrt<ll>({2, 3}, {3, 5});
	ENSURE(m == 15);
	ENSURE(a % 3 == 2);
	ENSURE(a % 5 == 3);
}

TEST(excrt_non_coprime_compatible) {
	// x ≡ 0 (mod 4), x ≡ 2 (mod 6)
	// gcd(4,6)=2, 2-0=2 divisible by 2: compatible
	auto [a, m] = excrt<ll>({0, 2}, {4, 6});
	ENSURE(a != -1);
	ENSURE(a % 4 == 0);
	ENSURE(a % 6 == 2);
}

TEST(excrt_non_coprime_incompatible) {
	// x ≡ 0 (mod 4), x ≡ 1 (mod 6)
	// gcd(4,6)=2, 1-0=1 not divisible by 2: incompatible
	auto [a, m] = excrt<ll>({0, 1}, {4, 6});
	ENSURE(a == -1);
}
