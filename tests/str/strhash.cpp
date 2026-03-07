#include "strhash.h"
#include "../test.h"

TEST(strhash_same_string) {
	StringHash h("abcdef");
	// substr(0, 6) should equal itself
	ENSURE(h.substr(0, 6) == h.substr(0, 6));
}

TEST(strhash_equal_substrings) {
	StringHash h("abcabc");
	// "abc" at [0,3) and [3,6) should have the same hash
	ENSURE(h.substr(0, 3) == h.substr(3, 6));
}

TEST(strhash_different_substrings) {
	StringHash h("abcdef");
	// Different substrings should (almost certainly) have different hashes
	ENSURE(h.substr(0, 3) != h.substr(3, 6));
}

TEST(strhash_single_char) {
	StringHash h("aaaa");
	// All single character substrings starting from 'a' should be equal
	ENSURE(h.substr(0, 1) == h.substr(1, 2));
	ENSURE(h.substr(1, 2) == h.substr(2, 3));
}

TEST(strhash_prefix) {
	StringHash h("abcdef");
	// Prefix [0, n) should hash differently from substrings
	ENSURE(h.substr(0, 6) != h.substr(0, 3));
}
