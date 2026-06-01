#include "math/sieve.h"
#include "doctest.h"

TEST_CASE("sieve_primes_count") {
	EularSieve s(100);
	// Primes up to 100: 25 primes
	REQUIRE(s.primes.size() == 25);
}

TEST_CASE("sieve_first_primes") {
	EularSieve s(30);
	vector<int> expected = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
	REQUIRE(s.primes == expected);
}

TEST_CASE("sieve_lpf") {
	EularSieve s(20);
	// Smallest prime factors
	REQUIRE(s.lpf[2] == 2);
	REQUIRE(s.lpf[4] == 2);
	REQUIRE(s.lpf[6] == 2);
	REQUIRE(s.lpf[9] == 3);
	REQUIRE(s.lpf[15] == 3);
	// Primes have lpf == themselves
	REQUIRE(s.lpf[7] == 7);
	REQUIRE(s.lpf[11] == 11);
}

TEST_CASE("sieve_euler_totient") {
	EularSieve s(20, eular_f);
	// phi(1)=1, phi(2)=1, phi(6)=2, phi(12)=4
	REQUIRE(s.fv[1] == 1);
	REQUIRE(s.fv[2] == 1);
	REQUIRE(s.fv[6] == 2);
	REQUIRE(s.fv[12] == 4);
}

TEST_CASE("sieve_mobius") {
	EularSieve s(30, mobius_f);
	// mu(1)=1, mu(p)=-1, mu(p^2)=0, mu(p*q)=1
	REQUIRE(s.fv[1] == 1);
	REQUIRE(s.fv[2] == -1);	// mu(2) = -1
	REQUIRE(s.fv[4] == 0);	// mu(4) = 0 (4=2^2)
	REQUIRE(s.fv[6] == 1);	// mu(6) = mu(2*3) = 1
	REQUIRE(s.fv[30] == -1); // mu(30) = mu(2*3*5) = -1
}

TEST_CASE("sieve_factor_count") {
	EularSieve s(20, factor_cnt_f);
	// d(1)=1, d(2)=2, d(4)=3, d(6)=4, d(12)=6
	REQUIRE(s.fv[1] == 1);
	REQUIRE(s.fv[2] == 2);
	REQUIRE(s.fv[4] == 3);
	REQUIRE(s.fv[6] == 4);
	REQUIRE(s.fv[12] == 6);
}
