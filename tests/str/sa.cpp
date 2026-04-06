#include "str/height.h"
#include "../test.h"

TEST(sa_banana) {
	// "banana": suffix array = [5,3,1,0,4,2]
	auto sa = suffix_array("banana");
	ENSURE(sa.size() == 6);
	ENSURE(sa[0] == 5);
	ENSURE(sa[1] == 3);
	ENSURE(sa[2] == 1);
	ENSURE(sa[3] == 0);
	ENSURE(sa[4] == 4);
	ENSURE(sa[5] == 2);
}

TEST(sa_aab) {
	// "aab": suffixes sorted: "aab"(0), "ab"(1), "b"(2) → sa=[0,1,2]
	auto sa = suffix_array("aab");
	ENSURE(sa.size() == 3);
	ENSURE(sa[0] == 0);
	ENSURE(sa[1] == 1);
	ENSURE(sa[2] == 2);
}

TEST(sa_single_char) {
	auto sa = suffix_array("a");
	ENSURE(sa.size() == 1);
	ENSURE(sa[0] == 0);
}

TEST(sa_repeated) {
	// "aaaa": suffixes sorted: "a"(3),"aa"(2),"aaa"(1),"aaaa"(0) → sa=[3,2,1,0]
	auto sa = suffix_array("aaaa");
	ENSURE(sa.size() == 4);
	ENSURE(sa[0] == 3);
	ENSURE(sa[1] == 2);
	ENSURE(sa[2] == 1);
	ENSURE(sa[3] == 0);
}

TEST(height_banana) {
	// height("banana") = [0,1,3,0,0,2]
	auto h = height("banana");
	ENSURE(h.size() == 6);
	ENSURE(h[0] == 0);
	ENSURE(h[1] == 1);
	ENSURE(h[2] == 3);
	ENSURE(h[3] == 0);
	ENSURE(h[4] == 0);
	ENSURE(h[5] == 2);
}

TEST(height_aab) {
	// sa=[0,1,2]: LCP("aab","ab")=1, LCP("ab","b")=0 → h=[0,1,0]
	auto h = height("aab");
	ENSURE(h.size() == 3);
	ENSURE(h[0] == 0);
	ENSURE(h[1] == 1);
	ENSURE(h[2] == 0);
}
