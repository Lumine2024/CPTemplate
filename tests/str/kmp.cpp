#include "str/kmp.h"
#include "doctest.h"

TEST_CASE("kmp_f_simple") {
	// "aabaa": failure function = [0,1,0,1,2]
	auto f = kmp_f("aabaa");
	REQUIRE(f.size() == 5);
	REQUIRE(f[0] == 0);
	REQUIRE(f[1] == 1);
	REQUIRE(f[2] == 0);
	REQUIRE(f[3] == 1);
	REQUIRE(f[4] == 2);
}

TEST_CASE("kmp_f_aaaa") {
	// "aaaa": failure function = [0,1,2,3]
	auto f = kmp_f("aaaa");
	REQUIRE(f[0] == 0);
	REQUIRE(f[1] == 1);
	REQUIRE(f[2] == 2);
	REQUIRE(f[3] == 3);
}

TEST_CASE("kmp_find_basic") {
	REQUIRE(kmp_find("abcabcabc", "abc") == 0);
	REQUIRE(kmp_find("abcabcabc", "cab") == 2);
	REQUIRE(kmp_find("abcabcabc", "xyz") == -1);
}

TEST_CASE("kmp_find_with_offset") {
	REQUIRE(kmp_find("abcabcabc", "abc", 1) == 3);
	REQUIRE(kmp_find("abcabcabc", "abc", 4) == 6);
	REQUIRE(kmp_find("abcabcabc", "abc", 7) == -1);
}

TEST_CASE("kmp_count_occurrences") {
	REQUIRE(kmp_count("abababab", "ab") == 4);
	REQUIRE(kmp_count("aaaa", "aa") == 3); // overlapping
	REQUIRE(kmp_count("abc", "xyz") == 0);
	REQUIRE(kmp_count("abc", "abc") == 1);
}

TEST_CASE("kmp_find_at_end") {
	REQUIRE(kmp_find("xyzabc", "abc") == 3);
}
