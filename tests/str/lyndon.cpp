#include "str/lyndon.h"
#include "../test.h"

TEST(lyndon_single_char) {
	auto v = duval("a");
	ENSURE(v.size() == 1);
	ENSURE(v[0] == "a");
}

TEST(lyndon_already_lyndon) {
	// "abc" is a Lyndon word
	auto v = duval("abc");
	ENSURE(v.size() == 1);
	ENSURE(v[0] == "abc");
}

TEST(lyndon_two_equal) {
	// "abab" = "ab" + "ab"
	auto v = duval("abab");
	ENSURE(v.size() == 2);
	ENSURE(v[0] == "ab");
	ENSURE(v[1] == "ab");
}

TEST(lyndon_abcabc) {
	// "abcabc" = "abc" + "abc"
	auto v = duval("abcabc");
	ENSURE(v.size() == 2);
	ENSURE(v[0] == "abc");
	ENSURE(v[1] == "abc");
}

TEST(lyndon_decreasing) {
	// "cba": each character is its own Lyndon word (non-increasing order)
	auto v = duval("cba");
	ENSURE(v.size() == 3);
	ENSURE(v[0] == "c");
	ENSURE(v[1] == "b");
	ENSURE(v[2] == "a");
}

TEST(lyndon_concatenation_preserved) {
	// Duval factorization concatenates back to original string
	string s = "abacaba";
	auto v = duval(s);
	string joined;
	for(const auto &w : v) joined += w;
	ENSURE(joined == s);
}

TEST(lyndon_all_same) {
	// "aaaa" = "a" + "a" + "a" + "a"
	auto v = duval("aaaa");
	ENSURE(v.size() == 4);
	for(const auto &w : v) ENSURE(w == "a");
}
