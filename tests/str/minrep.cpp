#include "str/minrep.h"
#include "../test.h"

TEST(minrep_already_min) {
	// "abc": all rotations are "abc","bca","cab"; min is "abc"
	ENSURE(minrep("abc") == "abc");
}

TEST(minrep_rotation_needed) {
	// "bca": rotations are "bca","cab","abc"; min is "abc"
	ENSURE(minrep("bca") == "abc");
}

TEST(minrep_repeated) {
	// "abab": rotations "abab","baba","abab","baba"; min is "abab"
	ENSURE(minrep("abab") == "abab");
}

TEST(minrep_single_char) {
	ENSURE(minrep("a") == "a");
}

TEST(minrep_all_same) {
	ENSURE(minrep("aaaa") == "aaaa");
}

TEST(minrep_descending) {
	// "cba": min rotation is "acb" (rot by 2)
	ENSURE(minrep("cba") == "acb");
}

TEST(minrep_banana) {
	// "banana": rotations include "ababna"? Let me compute: "banana","ananab","nanaba","anaban","nabana","abanan"
	// Sorted min: "abanan"
	ENSURE(minrep("banana") == "abanan");
}
