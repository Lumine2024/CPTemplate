#include "math/poly.h"
#include "doctest.h"

constexpr unsigned modulo = 998244353;
using Poly = Polynomial<modulo>;
using Z = Poly::Z;

void ensure_poly_eq(const Poly &poly, const vector<Z> &expect) {
	REQUIRE(poly.size() == expect.size());
	for(int i = 0; i < expect.size(); ++i) {
		REQUIRE(poly[i] == expect[i]);
	}
}

TEST_CASE("poly_init") {
	Poly a = {1, 2, 3, 4, 5};
	for(int i = 0; i < 5; ++i) {
		REQUIRE(a[i] == Z(i + 1));
	}
}
TEST_CASE("poly_add") {
	Poly a = {1, 2, 3, 4, 5};
	Poly b = {5, 4, 3, 2, 1};
	Poly c = a + b;
	for(int i = 0; i < 5; ++i) {
		REQUIRE(c[i] == Z(6));
	}
}
TEST_CASE("poly_add_different_sizes") {
	Poly a = {1, 2, 3, 4, 5};
	Poly b = {6, 7};
	Poly c = a + b;
	vector<Z> expect = {7, 9, 3, 4, 5};
	ensure_poly_eq(c, expect);
}
TEST_CASE("poly_sub_different_sizes") {
	Poly a = {10, 9, 8, 7};
	Poly b = {1, 2, 3};
	Poly c = a - b;
	vector<Z> expect = {9, 7, 5, 7};
	ensure_poly_eq(c, expect);
}
TEST_CASE("poly_mul_basic") {
	Poly a = {1, 2, 3};
	Poly b = {4, 5};
	Poly c = a * b;
	vector<Z> expect = {4, 13, 22, 15};
	ensure_poly_eq(c, expect);
}
TEST_CASE("poly_mod_xk") {
	Poly a = {3, 1, 4, 1, 5};
	ensure_poly_eq(a.mod_xk(3), {3, 1, 4});
	ensure_poly_eq(a.mod_xk(0), {});
}
TEST_CASE("poly_deriv") {
	Poly a = {5, 4, 3, 2};
	vector<Z> expect = {4, 6, 6};
	ensure_poly_eq(a.deriv(), expect);
}
TEST_CASE("poly_integ") {
	Poly a = {4, 6, 6};
	vector<Z> expect = {0, 4, 3, 2};
	ensure_poly_eq(a.integ(), expect);
}
TEST_CASE("poly_inv") {
	// fibonacci sequence's generation function: 1 / (-x^2 - x + 1)
	Poly den = {1, -1, -1};
	Poly res = den.inv(10);
	REQUIRE(res.size() == 10);
	vector<Z> fib = {1, 1, 2, 3, 5, 8, 13, 21, 34, 55};
	ensure_poly_eq(res, fib);
}
TEST_CASE("poly_inv_identity_mod_xk") {
	Poly a = {2, 3, 1, 4};
	Poly inv = a.inv(6);
	Poly prod = (a * inv).mod_xk(6);
	vector<Z> expect = {1, 0, 0, 0, 0, 0};
	ensure_poly_eq(prod, expect);
}
TEST_CASE("poly_ln_one_plus_x") {
	Poly a = {1, 1};
	Poly res = a.ln(5);
	vector<Z> expect = {
		0, 1, Z(0) - Z(1) / Z(2), Z(1) / Z(3), Z(0) - Z(1) / Z(4)
	};
	ensure_poly_eq(res, expect);
}
TEST_CASE("poly_exp_x") {
	Poly a = {0, 1};
	Poly res = a.exp(5);
	vector<Z> expect = {1, 1, Z(1) / Z(2), Z(1) / Z(6), Z(1) / Z(24)};
	ensure_poly_eq(res, expect);
}
TEST_CASE("poly_sqrt_one_plus_x") {
	Poly a = {1, 1};
	Poly res = a.sqrt(5);
	vector<Z> expect = {
		1, Z(1) / Z(2), Z(0) - Z(1) / Z(8), Z(1) / Z(16),
		Z(0) - Z(5) / Z(128)
	};
	ensure_poly_eq(res, expect);
}
