#include "str/manacher.h"
#include "doctest.h"

// Returns length of longest palindrome in s using Manacher output
static int longest_palindrome(const string &s) {
	auto dp = manacher(s);
	int mx = *max_element(dp.begin(), dp.end());
	return mx - 1;
}

TEST_CASE("manacher_single_char") {
	REQUIRE(longest_palindrome("a") == 1);
}

TEST_CASE("manacher_two_same") {
	REQUIRE(longest_palindrome("aa") == 2);
}

TEST_CASE("manacher_two_diff") {
	REQUIRE(longest_palindrome("ab") == 1);
}

TEST_CASE("manacher_odd_palindrome") {
	// "aba": longest palindrome is "aba" (length 3)
	REQUIRE(longest_palindrome("aba") == 3);
}

TEST_CASE("manacher_even_palindrome") {
	// "abba": longest palindrome is "abba" (length 4)
	REQUIRE(longest_palindrome("abba") == 4);
}

TEST_CASE("manacher_longer") {
	// "abacaba": longest palindrome is "abacaba" (length 7)
	REQUIRE(longest_palindrome("abacaba") == 7);
}

TEST_CASE("manacher_no_inner_palindrome") {
	// "abcde": longest palindrome has length 1
	REQUIRE(longest_palindrome("abcde") == 1);
}

TEST_CASE("manacher_all_same") {
	// "aaaa": longest palindrome is "aaaa" (length 4)
	REQUIRE(longest_palindrome("aaaa") == 4);
}

TEST_CASE("manacher_complex") {
	// "abaab": palindromes include "aba"(3), "aa"(2), "baab"(4)
	REQUIRE(longest_palindrome("abaab") == 4);
}
