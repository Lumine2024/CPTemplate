#pragma once
#include "ds/dynbitset.h"

DynamicBitSet ks_bitset(const vector<int> &val, int ma) {
	int sum = accumulate(val.begin(), val.end(), 0ll);
	DynamicBitSet ks(min(sum, ma) + 1);
	ks.setbit(0, true);
	for(int i : val) {
		ks |= (ks << i);
	}
	return ks;
}