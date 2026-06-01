#include "str/pam.h"
#include "doctest.h"

TEST_CASE("pam_pal_suffix_count_for_repeated_char") {
	PAM pam;
	REQUIRE(pam.insert('a') == 1);
	REQUIRE(pam.insert('a') == 2);
	REQUIRE(pam.insert('a') == 3);
}

TEST_CASE("pam_existing_node_reuse") {
	PAM pam;
	REQUIRE(pam.insert('a') == 1);
	REQUIRE(pam.insert('b') == 1);
	REQUIRE(pam.insert('a') == 2);
	REQUIRE(pam.insert('c') == 1);
	REQUIRE(pam.insert('a') == 2);
}
