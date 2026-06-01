#include "ds/valseg.h"
#include "valmonitor.h"
#include "doctest.h"

struct VSTMonitor {
	explicit VSTMonitor(int max_value) : ds(max_value) {}

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
	ValSeg ds;
	int cnt = 0;
};

TEST_CASE("vst_val_monitor_cases") {
	const int max_value = get_val_monitor_max_value();
	for(const auto &test_case : get_val_monitor_test_cases()) {
		VSTMonitor monitor(max_value);
		REQUIRE(run_val_monitor_operations(monitor, test_case.ops) ==
				test_case.anss);
	}
}
