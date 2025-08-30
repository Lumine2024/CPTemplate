
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;

template<class T, class F> concept binary_func = convertible_to<F, function<bool(T, T)>>;
template<class T1, class T2, class F> requires(binary_func<T1, F> &&convertible_to<T2, T1>) bool chkf(T1 &x, const T2 &y, F &&f) {
	if(f(static_cast<T1>(y), x)) {
		x = static_cast<T1>(y);
		return true;
	}
	return false;
}
template<class T1, class T2> bool chkmin(T1 &x, const T2 &y) {
	return chkf(x, y, less<T1>{});
}
template<class T1, class T2> bool chkmax(T1 &x, const T2 &y) {
	return chkf(x, y, greater<T1>{});
}

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

inline void solve() {
    
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
