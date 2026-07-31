#include "math/matrix.h"
#include "doctest.h"

TEST_CASE("matrix_unit") {
	auto I = Matrix<ll>::unit(3);
	for(int i = 0; i < 3; ++i) {
		for(int j = 0; j < 3; ++j) {
			REQUIRE(I[i][j] == (i == j ? 1LL : 0LL));
		}
	}
}

TEST_CASE("matrix_add_sub_and_compound_assignment") {
	Matrix<ll> a(2, 2), b(2, 2);
	a[0][0] = 1, a[0][1] = 2;
	a[1][0] = 3, a[1][1] = 4;
	b[0][0] = 5, b[0][1] = 6;
	b[1][0] = 7, b[1][1] = 8;

	auto sum = a + b;
	REQUIRE(sum[0][0] == 6);
	REQUIRE(sum[0][1] == 8);
	REQUIRE(sum[1][0] == 10);
	REQUIRE(sum[1][1] == 12);

	sum -= b;
	REQUIRE(sum[0][0] == 1);
	REQUIRE(sum[0][1] == 2);
	REQUIRE(sum[1][0] == 3);
	REQUIRE(sum[1][1] == 4);
}

TEST_CASE("matrix_multiplication_square_and_rectangular") {
	Matrix<ll> a(2, 2), b(2, 2);
	a[0][0] = 1, a[0][1] = 2;
	a[1][0] = 3, a[1][1] = 4;
	b[0][0] = 5, b[0][1] = 6;
	b[1][0] = 7, b[1][1] = 8;

	auto c = a * b;
	REQUIRE(c[0][0] == 19);
	REQUIRE(c[0][1] == 22);
	REQUIRE(c[1][0] == 43);
	REQUIRE(c[1][1] == 50);

	Matrix<int> left(2, 3);
	left[0][0] = 1, left[0][1] = 2, left[0][2] = 3;
	left[1][0] = 4, left[1][1] = 5, left[1][2] = 6;
	Matrix<ll> right(3, 2);
	right[0][0] = 7, right[0][1] = 8;
	right[1][0] = 9, right[1][1] = 10;
	right[2][0] = 11, right[2][1] = 12;

	Matrix<ll> promoted = left;
	auto rect = promoted * right;
	REQUIRE(rect[0][0] == 58);
	REQUIRE(rect[0][1] == 64);
	REQUIRE(rect[1][0] == 139);
	REQUIRE(rect[1][1] == 154);
}

TEST_CASE("matrix_mul_assign_and_identity") {
	Matrix<ll> a(2, 2);
	a[0][0] = 2, a[0][1] = 3;
	a[1][0] = 1, a[1][1] = 4;

	auto I = Matrix<ll>::unit(2);
	auto copy = a;
	copy *= I;
	REQUIRE(copy[0][0] == 2);
	REQUIRE(copy[0][1] == 3);
	REQUIRE(copy[1][0] == 1);
	REQUIRE(copy[1][1] == 4);
}
