#include "linbasis.h"
#include "../test.h"

TEST(linbasis_single_element) {
	LinearBasis_XOR basis;
	basis.insert(6);
	ENSURE(basis.query_max() == 6);
}

TEST(linbasis_two_independent) {
	// {4, 2}: basis = {4, 2}. Max XOR = 4^2 = 6.
	LinearBasis_XOR basis;
	basis.insert(4);
	basis.insert(2);
	ENSURE(basis.query_max() == 6);
}

TEST(linbasis_xor_span) {
	// {1, 2, 4}: basis = {4, 2, 1}. Max XOR = 7.
	LinearBasis_XOR basis;
	basis.insert(1);
	basis.insert(2);
	basis.insert(4);
	ENSURE(basis.query_max() == 7);
}

TEST(linbasis_dependent) {
	// {3, 5, 6}: 3^5=6, so 6 is dependent.
	// Basis: insert 3 → base[1]=3. insert 5 → 5^3=6? No: bit1 of 5 is 0, bit2 is 1.
	// Actually 5=101: bit2=1, base[2]=5. 3=011: bit1=1, base[1]=3. 6=110: bit2=1, 6^5=3=011, bit1=1, 3^3=0. Dependent.
	// Max: ans=0. 5>0 → ans=5. 5^3=6>5 → ans=6. Max=6.
	LinearBasis_XOR basis;
	basis.insert(3);
	basis.insert(5);
	basis.insert(6);
	ENSURE(basis.query_max() == 6);
}

TEST(linbasis_three_powers_of_two) {
	// {8, 4, 2}: all independent. Max = 8^4^2 = 14.
	LinearBasis_XOR basis;
	basis.insert(8);
	basis.insert(4);
	basis.insert(2);
	ENSURE(basis.query_max() == 14);
}

TEST(linbasis_zero_inserted) {
	// Inserting 0 has no effect on max
	LinearBasis_XOR basis;
	basis.insert(7);
	basis.insert(0);
	ENSURE(basis.query_max() == 7);
}

