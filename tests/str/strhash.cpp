#include "str/strhash.h"
#include "doctest.h"

TEST_CASE("strhash_same_string") {
	StringHash h("abcdef");
	// substr(0, 6) should equal itself
	REQUIRE(h.substr(0, 6) == h.substr(0, 6));
}

TEST_CASE("strhash_equal_substrings") {
	StringHash h("abcabc");
	// "abc" at [0,3) and [3,6) should have the same hash
	REQUIRE(h.substr(0, 3) == h.substr(3, 6));
}

TEST_CASE("strhash_different_substrings") {
	StringHash h("abcdef");
	// Different substrings should (almost certainly) have different hashes
	REQUIRE(h.substr(0, 3) != h.substr(3, 6));
}

TEST_CASE("strhash_single_char") {
	StringHash h("aaaa");
	// All single character substrings starting from 'a' should be equal
	REQUIRE(h.substr(0, 1) == h.substr(1, 2));
	REQUIRE(h.substr(1, 2) == h.substr(2, 3));
}

TEST_CASE("strhash_prefix") {
	StringHash h("abcdef");
	// Prefix [0, n) should hash differently from substrings
	REQUIRE(h.substr(0, 6) != h.substr(0, 3));
}
