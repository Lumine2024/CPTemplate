#include "math/bsgs.h"
#include "doctest.h"

TEST_CASE("bsgs_finds_small_discrete_log") {
	REQUIRE(mlog<17>(3, 13) == 4);
}

TEST_CASE("bsgs_handles_no_solution") {
	REQUIRE(mlog<7>(2, 3) == -1);
}
