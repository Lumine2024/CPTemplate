#include "math/fft.h"
#include "doctest.h"

static bool approx_eq(ld a, ld b) {
	return fabsl(a - b) < 1e-4l;
}

TEST_CASE("fft_multiply_basic") {
	// (1 + x) * (1 + x) = 1 + 2x + x^2
	vector<ld> a = {1.0l, 1.0l};
	vector<ld> b = {1.0l, 1.0l};
	auto c = multiply(a, b);
	REQUIRE(c.size() == 3);
	REQUIRE(approx_eq(c[0], 1.0l));
	REQUIRE(approx_eq(c[1], 2.0l));
	REQUIRE(approx_eq(c[2], 1.0l));
}

TEST_CASE("fft_multiply_constant") {
	// 3 * (1 + 2x) = 3 + 6x
	vector<ld> a = {3.0l};
	vector<ld> b = {1.0l, 2.0l};
	auto c = multiply(a, b);
	REQUIRE(c.size() == 2);
	REQUIRE(approx_eq(c[0], 3.0l));
	REQUIRE(approx_eq(c[1], 6.0l));
}

TEST_CASE("fft_multiply_larger") {
	// (1 + x + x^2) * (1 + x) = 1 + 2x + 2x^2 + x^3
	vector<ld> a = {1.0l, 1.0l, 1.0l};
	vector<ld> b = {1.0l, 1.0l};
	auto c = multiply(a, b);
	REQUIRE(c.size() == 4);
	REQUIRE(approx_eq(c[0], 1.0l));
	REQUIRE(approx_eq(c[1], 2.0l));
	REQUIRE(approx_eq(c[2], 2.0l));
	REQUIRE(approx_eq(c[3], 1.0l));
}

TEST_CASE("fft_multiply_integers") {
	// (2 + 3x) * (4 + 5x) = 8 + 22x + 15x^2
	vector<ld> a = {2.0l, 3.0l};
	vector<ld> b = {4.0l, 5.0l};
	auto c = multiply(a, b);
	REQUIRE(c.size() == 3);
	REQUIRE(approx_eq(c[0], 8.0l));
	REQUIRE(approx_eq(c[1], 22.0l));
	REQUIRE(approx_eq(c[2], 15.0l));
}

TEST_CASE("fft_multiply_zero") {
	// 0 * anything = 0
	vector<ld> a = {0.0l};
	vector<ld> b = {3.0l, 5.0l};
	auto c = multiply(a, b);
	for(ld v : c) REQUIRE(approx_eq(v, 0.0l));
}
