#include "str/height.h"
#include "doctest.h"

TEST_CASE("sa_banana") {
	// "banana": suffix array = [5,3,1,0,4,2]
	auto sa = suffix_array("banana");
	REQUIRE(sa.size() == 6);
	REQUIRE(sa[0] == 5);
	REQUIRE(sa[1] == 3);
	REQUIRE(sa[2] == 1);
	REQUIRE(sa[3] == 0);
	REQUIRE(sa[4] == 4);
	REQUIRE(sa[5] == 2);
}

TEST_CASE("sa_aab") {
	// "aab": suffixes sorted: "aab"(0), "ab"(1), "b"(2) → sa=[0,1,2]
	auto sa = suffix_array("aab");
	REQUIRE(sa.size() == 3);
	REQUIRE(sa[0] == 0);
	REQUIRE(sa[1] == 1);
	REQUIRE(sa[2] == 2);
}

TEST_CASE("sa_single_char") {
	auto sa = suffix_array("a");
	REQUIRE(sa.size() == 1);
	REQUIRE(sa[0] == 0);
}

TEST_CASE("sa_repeated") {
	// "aaaa": suffixes sorted: "a"(3),"aa"(2),"aaa"(1),"aaaa"(0) → sa=[3,2,1,0]
	auto sa = suffix_array("aaaa");
	REQUIRE(sa.size() == 4);
	REQUIRE(sa[0] == 3);
	REQUIRE(sa[1] == 2);
	REQUIRE(sa[2] == 1);
	REQUIRE(sa[3] == 0);
}

TEST_CASE("height_banana") {
	// height("banana") = [0,1,3,0,0,2]
	auto h = height("banana");
	REQUIRE(h.size() == 6);
	REQUIRE(h[0] == 0);
	REQUIRE(h[1] == 1);
	REQUIRE(h[2] == 3);
	REQUIRE(h[3] == 0);
	REQUIRE(h[4] == 0);
	REQUIRE(h[5] == 2);
}

TEST_CASE("height_aab") {
	// sa=[0,1,2]: LCP("aab","ab")=1, LCP("ab","b")=0 → h=[0,1,0]
	auto h = height("aab");
	REQUIRE(h.size() == 3);
	REQUIRE(h[0] == 0);
	REQUIRE(h[1] == 1);
	REQUIRE(h[2] == 0);
}
