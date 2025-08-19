#pragma once
#include "../constants.hpp"

struct DynamicBitSet {
    explicit DynamicBitSet(int n = 0) : nums((n + 63) >> 6, 0), sz(n) {}
    void resize(int n) {
        nums.resize(n);
        sz = n;
    }
    bool getbit(int x) const {
        int u = x >> 6;
        int v = x - (u << 6);
        return ((nums[u] >> v) & 1) == 1;
    }
    void setbit(int x, bool val) {
        int u = x >> 6;
        int v = x - (u << 6);
        if(!val) {
            ull d = (ull)-1;
            d ^= (1ull << v);
            nums[u] &= d;
        } else {
            nums[u] |= (1ull << v);
        }
    }
    DynamicBitSet &operator&=(const DynamicBitSet &other) {
        for(int i = 0; i < nums.size(); ++i) {
            nums[i] &= other.nums[i];
        }
        return *this;
    }
    DynamicBitSet operator&(const DynamicBitSet &other) const {
        DynamicBitSet ret = *this;
        ret &= other;
        return ret;
    }
    DynamicBitSet &operator|=(const DynamicBitSet &other) {
        for(int i = 0; i < nums.size(); ++i) {
            nums[i] |= other.nums[i];
        }
        return *this;
    }
    DynamicBitSet operator|(const DynamicBitSet &other) const {
        DynamicBitSet ret = *this;
        ret |= other;
        return ret;
    }
    DynamicBitSet &operator^=(const DynamicBitSet &other) {
        for(int i = 0; i < nums.size(); ++i) {
            nums[i] ^= other.nums[i];
        }
        return *this;
    }
    DynamicBitSet operator^(const DynamicBitSet &other) const {
        DynamicBitSet ret = *this;
        ret ^= other;
        return ret;
    }
    bool allzero() const {
        for(ull i : nums) {
            if(i != 0ull) return false;
        }
        return true;
    }
    int size() const {return sz;}
private:
    vector<ull> nums;
    int sz;
};