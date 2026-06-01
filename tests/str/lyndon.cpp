#include "str/lyndon.h"
#include "doctest.h"

TEST_CASE("lyndon_single_char") {
	auto v = duval("a");
	REQUIRE(v.size() == 1);
	REQUIRE(v[0] == "a");
}

TEST_CASE("lyndon_already_lyndon") {
	// "abc" is a Lyndon word
	auto v = duval("abc");
	REQUIRE(v.size() == 1);
	REQUIRE(v[0] == "abc");
}

TEST_CASE("lyndon_two_equal") {
	// "abab" = "ab" + "ab"
	auto v = duval("abab");
	REQUIRE(v.size() == 2);
	REQUIRE(v[0] == "ab");
	REQUIRE(v[1] == "ab");
}

TEST_CASE("lyndon_abcabc") {
	// "abcabc" = "abc" + "abc"
	auto v = duval("abcabc");
	REQUIRE(v.size() == 2);
	REQUIRE(v[0] == "abc");
	REQUIRE(v[1] == "abc");
}

TEST_CASE("lyndon_decreasing") {
	// "cba": each character is its own Lyndon word (non-increasing order)
	auto v = duval("cba");
	REQUIRE(v.size() == 3);
	REQUIRE(v[0] == "c");
	REQUIRE(v[1] == "b");
	REQUIRE(v[2] == "a");
}

TEST_CASE("lyndon_concatenation_preserved") {
	// Duval factorization concatenates back to original string
	string s = "abacaba";
	auto v = duval(s);
	string joined;
	for(const auto &w : v) joined += w;
	REQUIRE(joined == s);
}

TEST_CASE("lyndon_all_same") {
	// "aaaa" = "a" + "a" + "a" + "a"
	auto v = duval("aaaa");
	REQUIRE(v.size() == 4);
	for(const auto &w : v) REQUIRE(w == "a");
}
