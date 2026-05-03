#include "ds/treap.h"
#include "valmonitor.h"
#include "../test.h"

struct TreapMonitor {
	void insert(int x) {
		ds.insert(x);
		++cnt;
	}
	void erase(int x) {
		ds.erase(x);
		--cnt;
	}
	int rank_by_value(int x) const {
		return ds.qrv(x);
	}
	int value_by_rank(int k) const {
		if(k < 0 || k >= cnt) return kValMonitorNoValue;
		return ds.qvr(k);
	}
	int max_less(int x) const {
		int rk = ds.qrv(x);
		if(rk == 0) return kValMonitorNoValue;
		return ds.qvr(rk - 1);
	}
	int min_greater(int x) const {
		int rk = ds.qrv(x + 1);
		if(rk == cnt) return kValMonitorNoValue;
		return ds.qvr(rk);
	}

private:
	mutable Treap ds;
	int cnt = 0;
};

TEST(treap_val_monitor_cases) {
	for(const auto &test_case : get_val_monitor_test_cases()) {
		TreapMonitor monitor;
		ENSURE(run_val_monitor_operations(monitor, test_case.ops) ==
			   test_case.anss);
	}
}
