#pragma once
#include "common.h"

constexpr ll modulo = 998244353;

struct Dislocation {
	Dislocation() = delete;
	static ll get(int i) {
		return nums[i];
	}

private:
	static constexpr ll maxn = 500005;
	static inline ll nums[maxn];
	static inline int init = [] {
		nums[0] = nums[2] = 1;
		for(ll i = 3; i < maxn; ++i) {
			nums[i] = (i - 1) * (nums[i - 1] + nums[i - 2]) % modulo;
		}
		return 0;
	}();
};
