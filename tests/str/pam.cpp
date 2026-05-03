#include "str/pam.h"
#include "../test.h"

TEST(pam_pal_suffix_count_for_repeated_char) {
	PAM pam;
	ENSURE(pam.insert('a') == 1);
	ENSURE(pam.insert('a') == 2);
	ENSURE(pam.insert('a') == 3);
}

TEST(pam_existing_node_reuse) {
	PAM pam;
	ENSURE(pam.insert('a') == 1);
	ENSURE(pam.insert('b') == 1);
	ENSURE(pam.insert('a') == 2);
	ENSURE(pam.insert('c') == 1);
	ENSURE(pam.insert('a') == 2);
}
