#pragma once
#include "common.h"

struct DynamicBitSet {
	explicit DynamicBitSet(int n = 0) : nums((n + 63) >> 6, 0), sz(n) {}
	void resize(int n) {
		nums.resize((n + 63) >> 6);
		sz = n;
	}
	bool getbit(int x) const {
		int u = x >> 6, v = x & 63;
		return ((nums[u] >> v) & 1) == 1;
	}
	void setbit(int x, bool val) {
		int u = x >> 6, v = x & 63;
		if(!val) {
			nums[u] &= (~(1ull << v));
		} else {
			nums[u] |= (1ull << v);
		}
	}
	void flipbit(int x) {
		setbit(x, !getbit(x));
	}
	DynamicBitSet &operator&=(const DynamicBitSet &other) {
		for(int i = 0; i < nums.size(); ++i) nums[i] &= other.nums[i];
		return *this;
	}
	DynamicBitSet operator&(const DynamicBitSet &other) const {
		DynamicBitSet ret = *this;
		ret &= other;
		return ret;
	}
	DynamicBitSet &operator|=(const DynamicBitSet &other) {
		for(int i = 0; i < nums.size(); ++i) nums[i] |= other.nums[i];
		return *this;
	}
	DynamicBitSet operator|(const DynamicBitSet &other) const {
		DynamicBitSet ret = *this;
		ret |= other;
		return ret;
	}
	DynamicBitSet &operator^=(const DynamicBitSet &other) {
		for(int i = 0; i < nums.size(); ++i) nums[i] ^= other.nums[i];
		return *this;
	}
	DynamicBitSet operator^(const DynamicBitSet &other) const {
		DynamicBitSet ret = *this;
		ret ^= other;
		return ret;
	}
	DynamicBitSet &operator<<=(int z) {
		int block = z >> 6, rem = z & 63, n = nums.size();
		if(rem == 0) {
			for(int i = n - 1; i >= block; --i) nums[i] = nums[i - block];
			fill(nums.begin(), nums.begin() + min(block, n), 0);
		} else {
			ull o1 = 0, o0 = 0;
			for(int i = n - block - 1; i >= 0; --i) {
				o0 = (nums[i] << rem);
				o1 |= (nums[i] >> (64 - rem));
				if(i + block + 1 < n) nums[i + block + 1] = o1;
				o1 = o0;
			}
			fill(nums.begin(), nums.begin() + min(block, n), 0);
			if(block < n) nums[block] = o0;
		}
		return *this;
	}
	DynamicBitSet operator<<(int z) const {
		DynamicBitSet ret = *this;
		ret <<= z;
		return ret;
	}
	DynamicBitSet &operator>>=(int z) {
		int block = z >> 6, rem = z & 63, n = nums.size();
		if(rem == 0) {
			for(int i = 0; i < n - block; ++i) nums[i] = nums[i + block];
			fill(nums.end() - min(n, block), nums.end(), 0);
		} else {
			ull o0 = 0, o1 = 0;
			for(int i = 0; i + block < n; ++i) {
				o1 |= (nums[i + block] << (64 - rem));
				o0 = (nums[i + block] >> rem);
				if(i != 0) nums[i - 1] = o1;
				o1 = o0;
			}
			fill(nums.end() - min(n, block + 1), nums.end(), 0);
			if(block <= n) nums[n - block - 1] = o0;
		}
		return *this;
	}
	DynamicBitSet operator>>(int z) const {
		DynamicBitSet ret = *this;
		ret >>= z;
		return ret;
	}
	bool allzero() const {
		int block = sz >> 6, rem = sz & 63;
		for(int i = 0; i < block; ++i) {
			if(nums[i] != 0ull) return false;
		}
		for(int i = block << 6; i < sz; ++i) {
			if(getbit(i)) return false;
		}
		return true;
	}
	int size() const {
		return sz;
	}
	int count() const {
		if(nums.empty()) return 0;
		int ans = 0;
		for(int i = 0; i < nums.size() - 1; ++i) {
			ans += __builtin_popcountll(nums[i]);
		}
		for(int i = int(nums.size() * 64) - 64; i < sz; ++i) {
			ans += int(getbit(i));
		}
		return ans;
	}

private:
	vector<ull> nums;
	int sz;
};
