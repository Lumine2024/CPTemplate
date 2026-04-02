#pragma once
#include "common.h"

template<ll modulo, ll maxn = 500005> struct Dislocation {
	Dislocation() = delete;
	static ll get(int i) {
		ensure_init();
		return nums[i];
	}

private:
	static inline ll nums[maxn];
	static inline bool inited = false;
	static void ensure_init() {
		if(inited) return;
		nums[0] = nums[2] = 1;
		for(ll i = 3; i < maxn; ++i) {
			nums[i] = (i - 1) * (nums[i - 1] + nums[i - 2]) % modulo;
		}
		return 0;
	}
};
