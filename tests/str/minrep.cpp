#include "str/minrep.h"
#include "doctest.h"

TEST_CASE("minrep_already_min") {
	// "abc": all rotations are "abc","bca","cab"; min is "abc"
	REQUIRE(minrep("abc") == "abc");
}

TEST_CASE("minrep_rotation_needed") {
	// "bca": rotations are "bca","cab","abc"; min is "abc"
	REQUIRE(minrep("bca") == "abc");
}

TEST_CASE("minrep_repeated") {
	// "abab": rotations "abab","baba","abab","baba"; min is "abab"
	REQUIRE(minrep("abab") == "abab");
}

TEST_CASE("minrep_single_char") {
	REQUIRE(minrep("a") == "a");
}

TEST_CASE("minrep_all_same") {
	REQUIRE(minrep("aaaa") == "aaaa");
}

TEST_CASE("minrep_descending") {
	// "cba": min rotation is "acb" (rot by 2)
	REQUIRE(minrep("cba") == "acb");
}

TEST_CASE("minrep_banana") {
	// "banana": rotations include "ababna"? Let me compute:
	// "banana","ananab","nanaba","anaban","nabana","abanan" Sorted min:
	// "abanan"
	REQUIRE(minrep("banana") == "abanan");
}
