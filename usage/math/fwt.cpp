#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

constexpr ll modulo = 998244353;

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

ll modadd(ll a, ll b) {
    a += b;
    if(a >= modulo) a -= modulo;
    return a;
}
ll modsub(ll a, ll b) {
    a -= b;
    if(a < 0) a += modulo;
    return a;
}

void fwt_and(vector<ll> &nums, bool invert) {
    int n = nums.size();
    for(ll x = 2; x <= n; x <<= 1) {
        ll k = x >> 1;
        for (ll i = 0; i < n; i += x) {
            for (ll j = 0; j < k; j++) {
                if(invert) {
                    nums[i + j] = modsub(nums[i + j], nums[i + j + k]);
                } else {
                    nums[i + j] = modadd(nums[i + j], nums[i + j + k]);
                }
            }
        }
    }
}

void fwt_or(vector<ll> &nums, bool invert) {
    int n = nums.size();
    for (ll x = 2; x <= n; x <<= 1) {
        ll k = x >> 1;
        for (ll i = 0; i < n; i += x) {
            for (ll j = 0; j < k; j++) {
                if(invert) {
                    nums[i + j + k] = modsub(nums[i + j + k], nums[i + j]);
                } else {
                    nums[i + j + k] = modadd(nums[i + j + k], nums[i + j]);
                }
            }
        }
    }
}

void fwt_xor(vector<ll> &nums, bool invert) {
    int n = nums.size();
    for (ll x = 2; x <= n; x <<= 1) {
        ll k = x >> 1;
        for (ll i = 0; i < n; i += x) {
            for (ll j = 0; j < k; j++) {
                nums[i + j] = modadd(nums[i + j], nums[i + j + k]);
                nums[i + j + k] = modsub(nums[i + j], modadd(nums[i + j + k], nums[i + j + k]));
                if(invert) {
                    nums[i + j] = modulo - nums[i + j];
                    nums[i + j + k] = modulo - nums[i + j + k];
                }
            }
        }
    }
}

inline void solve() {

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n = 1;
    // cin >> n;
    while(n--) {
        solve();
    }
    return 0;
}