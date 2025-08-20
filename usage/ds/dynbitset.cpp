// Standalone C++ file generated from ds/dynbitset.hpp
// Can be directly submitted to online judges

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;

inline constexpr ll modulo = 998244353, g = 3, inf = 0x3f3f3f3f3f3f3f3f;
inline constexpr int maxn = 100005, infint = 0x3f3f3f3f;
inline constexpr ld eps = 1e-9l, pi = 3.14159265358979323846264338327950288l, infld = 1e12l;

inline ll qpow(ll x, ll n) {
    ll ret = 1;
    for(; n != 0; n >>= 1, x = x * x % modulo) {
        if(n & 1) ret = ret * x % modulo;
    }
    return ret;
}

template<class T, class F> bool chkf(T &x, const T &y, F &&f) {
    if(f(y, x)) {
        x = y;
        return true;
    }
    return false;
}
template<class T> bool chkmin(T &x, const T &y) {
    return chkf(x, y, less{});
}
template<class T> bool chkmax(T &x, const T &y) {
    return chkf(x, y, greater{});
}

// === ds/dynbitset.hpp ===

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

// Example usage:
inline void solve() {
    // Add your solution code here using the template above
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
