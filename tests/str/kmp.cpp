#include "str/kmp.h"
#include "../test.h"

TEST(kmp_f_simple) {
	// "aabaa": failure function = [0,1,0,1,2]
	auto f = kmp_f("aabaa");
	ENSURE(f.size() == 5);
	ENSURE(f[0] == 0);
	ENSURE(f[1] == 1);
	ENSURE(f[2] == 0);
	ENSURE(f[3] == 1);
	ENSURE(f[4] == 2);
}

TEST(kmp_f_aaaa) {
	// "aaaa": failure function = [0,1,2,3]
	auto f = kmp_f("aaaa");
	ENSURE(f[0] == 0);
	ENSURE(f[1] == 1);
	ENSURE(f[2] == 2);
	ENSURE(f[3] == 3);
}

TEST(kmp_find_basic) {
	ENSURE(kmp_find("abcabcabc", "abc") == 0);
	ENSURE(kmp_find("abcabcabc", "cab") == 2);
	ENSURE(kmp_find("abcabcabc", "xyz") == -1);
}

TEST(kmp_find_with_offset) {
	ENSURE(kmp_find("abcabcabc", "abc", 1) == 3);
	ENSURE(kmp_find("abcabcabc", "abc", 4) == 6);
	ENSURE(kmp_find("abcabcabc", "abc", 7) == -1);
}

TEST(kmp_count_occurrences) {
	ENSURE(kmp_count("abababab", "ab") == 4);
	ENSURE(kmp_count("aaaa", "aa") == 3); // overlapping
	ENSURE(kmp_count("abc", "xyz") == 0);
	ENSURE(kmp_count("abc", "abc") == 1);
}

TEST(kmp_find_at_end) {
	ENSURE(kmp_find("xyzabc", "abc") == 3);
}
