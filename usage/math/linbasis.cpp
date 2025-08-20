// Standalone C++ file generated from math/linbasis.hpp
// Can be directly submitted to online judges

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;

inline constexpr ll inf = 0x3f3f3f3f3f3f3f3f;
inline constexpr int maxn = 100005, infint = 0x3f3f3f3f;
inline constexpr ld eps = 1e-9l, infld = 1e12l;

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

// === math/linbasis.hpp ===

struct LinearBasis_XOR {
	LinearBasis_XOR() : base(61) {}
	void insert(ll val) {
		for(int i = 60; i >= 0; --i) {
			if(((val >> i) & 1) == 0) continue;
			if(base[i] == 0) {
				base[i] = val;
				return;
			}
			val ^= base[i];
		}
	}
	ll query_max() const {
		ll ans = 0;
		for(int i = 60; i >= 0; --i) {
			if((ans ^ base[i]) > ans) {
				ans ^= base[i];
			}
		}
		return ans;
	}
private:
	vector<ll> base;
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
