#include "math/bsgs.h"
#include "../test.h"

TEST(bsgs_finds_small_discrete_log) {
	ENSURE(mlog<17>(3, 13) == 4);
}

TEST(bsgs_handles_no_solution) {
	ENSURE(mlog<7>(2, 3) == -1);
}
