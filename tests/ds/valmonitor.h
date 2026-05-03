#pragma once
#include "common.h"

constexpr int kValMonitorNoValue = -1;

enum QueryType : uint8_t {
	kInsert = 0,
	kErase,
	kRankByValue,
	kValueByRank,
	kMaxLess,
	kMinGreater,
};

struct Operation {
	QueryType type;
	int val;
};

struct ValMonitorTestCase {
	const char *name;
	vector<Operation> ops;
	vector<int> anss;
};

vector<ValMonitorTestCase> get_val_monitor_test_cases() {
	return {{"empty queries nothing",
			 {

			 },
			 {}},
			{"rank kth predecessor successor with duplicates",
			 {
				 {kInsert, 5},
				 {kInsert, 1},
				 {kInsert, 3},
				 {kInsert, 3},
				 {kRankByValue, 0},
				 {kRankByValue, 1},
				 {kRankByValue, 3},
				 {kRankByValue, 4},
				 {kValueByRank, 0},
				 {kValueByRank, 1},
				 {kValueByRank, 2},
				 {kValueByRank, 3},
				 {kMaxLess, 1},
				 {kMaxLess, 4},
				 {kMinGreater, 3},
				 {kMinGreater, 5},
			 },
			 {
				 0,
				 0,
				 1,
				 3,
				 1,
				 3,
				 3,
				 5,
				 kValMonitorNoValue,
				 3,
				 5,
				 kValMonitorNoValue,
			 }},
			{"erase keeps multiplicity consistent",
			 {
				 {kInsert, 2},
				 {kInsert, 2},
				 {kInsert, 4},
				 {kInsert, 6},
				 {kErase, 2},
				 {kRankByValue, 4},
				 {kValueByRank, 2},
				 {kMaxLess, 2},
				 {kMinGreater, 4},
				 {kErase, 2},
				 {kErase, 4},
				 {kRankByValue, 6},
				 {kValueByRank, 0},
				 {kMinGreater, 6},
			 },
			 {
				 1,
				 6,
				 kValMonitorNoValue,
				 6,
				 0,
				 6,
				 kValMonitorNoValue,
			 }},
			{"zero boundary and interleaved updates",
			 {
				 {kInsert, 0},
				 {kInsert, 7},
				 {kInsert, 1},
				 {kInsert, 0},
				 {kInsert, 9},
				 {kMaxLess, 0},
				 {kMinGreater, 0},
				 {kRankByValue, 1},
				 {kValueByRank, 1},
				 {kErase, 0},
				 {kRankByValue, 1},
				 {kMaxLess, 1},
				 {kMinGreater, 8},
			 },
			 {
				 kValMonitorNoValue,
				 1,
				 2,
				 0,
				 1,
				 0,
				 9,
			 }}};
}

inline int get_val_monitor_max_value() {
	int max_value = 0;
	for(const auto &test_case : get_val_monitor_test_cases()) {
		for(const auto &op : test_case.ops) {
			max_value = max(max_value, op.val);
		}
	}
	return max_value;
}

template<class Monitor>
vector<int> run_val_monitor_operations(Monitor &monitor,
									   const vector<Operation> &ops) {
	vector<int> ret;
	for(const auto &op : ops) {
		switch(op.type) {
			case kInsert:
				monitor.insert(op.val);
				break;
			case kErase:
				monitor.erase(op.val);
				break;
			case kRankByValue:
				ret.push_back(monitor.rank_by_value(op.val));
				break;
			case kValueByRank:
				ret.push_back(monitor.value_by_rank(op.val));
				break;
			case kMaxLess:
				ret.push_back(monitor.max_less(op.val));
				break;
			case kMinGreater:
				ret.push_back(monitor.min_greater(op.val));
				break;
		}
	}
	return ret;
}
