#include "str/zfunc.h"
#include "../test.h"

TEST(zfunc_basic) {
	// "aabxaa": z = [0, 1, 0, 0, 2, 1]
	auto z = zfn("aabxaa");
	ENSURE(z.size() == 6);
	ENSURE(z[0] == 0);  // by convention z[0] is 0 or n
	ENSURE(z[1] == 1);
	ENSURE(z[2] == 0);
	ENSURE(z[3] == 0);
	ENSURE(z[4] == 2);
	ENSURE(z[5] == 1);
}

TEST(zfunc_all_same) {
	// "aaaa": z = [0, 3, 2, 1]
	auto z = zfn("aaaa");
	ENSURE(z[0] == 0);
	ENSURE(z[1] == 3);
	ENSURE(z[2] == 2);
	ENSURE(z[3] == 1);
}

TEST(zfunc_all_distinct) {
	// "abcd": z = [0, 0, 0, 0]
	auto z = zfn("abcd");
	ENSURE(z[0] == 0);
	ENSURE(z[1] == 0);
	ENSURE(z[2] == 0);
	ENSURE(z[3] == 0);
}

TEST(zfunc_pattern_matching) {
	// Pattern search: find "ab" in "ababab" using z-function
	// Concatenate pattern + '$' + text, compute z
	string s = "ab$ababab";
	auto z = zfn(s);
	int pattern_len = 2;
	int count = 0;
	for(int i = 3; i < (int)s.size(); ++i) {
		if(z[i] >= pattern_len) ++count;
	}
	ENSURE(count == 3);
}

TEST(zfunc_single_char) {
	auto z = zfn("a");
	ENSURE(z.size() == 1);
	ENSURE(z[0] == 0);
}
