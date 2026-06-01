#include "str/zfunc.h"
#include "doctest.h"

TEST_CASE("zfunc_basic") {
	// "aabxaa": z = [0, 1, 0, 0, 2, 1]
	auto z = zfn("aabxaa");
	REQUIRE(z.size() == 6);
	REQUIRE(z[0] == 0); // by convention z[0] is 0 or n
	REQUIRE(z[1] == 1);
	REQUIRE(z[2] == 0);
	REQUIRE(z[3] == 0);
	REQUIRE(z[4] == 2);
	REQUIRE(z[5] == 1);
}

TEST_CASE("zfunc_all_same") {
	// "aaaa": z = [0, 3, 2, 1]
	auto z = zfn("aaaa");
	REQUIRE(z[0] == 0);
	REQUIRE(z[1] == 3);
	REQUIRE(z[2] == 2);
	REQUIRE(z[3] == 1);
}

TEST_CASE("zfunc_all_distinct") {
	// "abcd": z = [0, 0, 0, 0]
	auto z = zfn("abcd");
	REQUIRE(z[0] == 0);
	REQUIRE(z[1] == 0);
	REQUIRE(z[2] == 0);
	REQUIRE(z[3] == 0);
}

TEST_CASE("zfunc_pattern_matching") {
	// Pattern search: find "ab" in "ababab" using z-function
	// Concatenate pattern + '$' + text, compute z
	string s = "ab$ababab";
	auto z = zfn(s);
	int pattern_len = 2;
	int count = 0;
	for(int i = 3; i < (int)s.size(); ++i) {
		if(z[i] >= pattern_len) ++count;
	}
	REQUIRE(count == 3);
}

TEST_CASE("zfunc_single_char") {
	auto z = zfn("a");
	REQUIRE(z.size() == 1);
	REQUIRE(z[0] == 0);
}
