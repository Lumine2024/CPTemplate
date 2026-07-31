#include "math/linbasis.h"
#include "doctest.h"

TEST_CASE("linbasis_single_element") {
	LinearBasis basis;
	basis.insert(6);
	REQUIRE(basis.max_xor() == 6);
}

TEST_CASE("linbasis_two_independent") {
	// {4, 2}: basis = {4, 2}. Max XOR = 4^2 = 6.
	LinearBasis basis;
	basis.insert(4);
	basis.insert(2);
	REQUIRE(basis.max_xor() == 6);
}

TEST_CASE("linbasis_xor_span") {
	// {1, 2, 4}: basis = {4, 2, 1}. Max XOR = 7.
	LinearBasis basis;
	basis.insert(1);
	basis.insert(2);
	basis.insert(4);
	REQUIRE(basis.max_xor() == 7);
}

TEST_CASE("linbasis_dependent") {
	// {3, 5, 6}: 3^5=6, so 6 is dependent.
	// Basis: insert 3 → base[1]=3. insert 5 → 5^3=6? No: bit1 of 5 is 0, bit2
	// is 1. Actually 5=101: bit2=1, base[2]=5. 3=011: bit1=1, base[1]=3. 6=110:
	// bit2=1, 6^5=3=011, bit1=1, 3^3=0. Dependent. Max: ans=0. 5>0 → ans=5.
	// 5^3=6>5 → ans=6. Max=6.
	LinearBasis basis;
	basis.insert(3);
	basis.insert(5);
	basis.insert(6);
	REQUIRE(basis.max_xor() == 6);
}

TEST_CASE("linbasis_three_powers_of_two") {
	// {8, 4, 2}: all independent. Max = 8^4^2 = 14.
	LinearBasis basis;
	basis.insert(8);
	basis.insert(4);
	basis.insert(2);
	REQUIRE(basis.max_xor() == 14);
}

TEST_CASE("linbasis_zero_inserted") {
	// Inserting 0 has no effect on max
	LinearBasis basis;
	basis.insert(7);
	basis.insert(0);
	REQUIRE(basis.max_xor() == 7);
}
