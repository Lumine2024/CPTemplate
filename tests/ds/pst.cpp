#include "ds/pst.h"
#include "../test.h"

TEST(pst_kth_smallest_in_range) {
	PST pst(5);
	pst.update(2);
	pst.update(0);
	pst.update(3);
	pst.update(2);

	ENSURE(pst.query(1, 1, 4) == 0);
	ENSURE(pst.query(2, 1, 4) == 2);
	ENSURE(pst.query(3, 1, 4) == 2);
	ENSURE(pst.query(4, 1, 4) == 3);
	ENSURE(pst.query(1, 2, 3) == 0);
	ENSURE(pst.query(2, 2, 3) == 3);
}
