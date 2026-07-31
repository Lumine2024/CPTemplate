#pragma once
#include "common.h"

struct MyHash {
    ull operator()(ll x) const noexcept {
        ull v = ull(x) + c;
        v += 0x9e3779b97f4a7c15;
        v = (v ^ (v >> 30)) * 0xbf58476d1ce4e5b9;
        v = (v ^ (v >> 27)) * 0x94d049bb133111eb;
        return v ^ (v >> 31);
    }

private:
    static inline const ull c =
        chrono::steady_clock::now().time_since_epoch().count();
};
