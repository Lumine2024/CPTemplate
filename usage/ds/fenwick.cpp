#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

struct Fenwick {
	explicit Fenwick(int n) : n(n), nums(n + 1, 0) {}
	ll query(int x) const {
		ll ans = 0;
		for(; x; x -= lbit(x)) {
			ans += nums[x];
		}
		return ans;
	}
	void update(int x, ll v) {
		for(; x <= n; x += lbit(x)) {
			nums[x] += v;
		}
	}
private:
	vector<ll> nums;
	int n;
	static int lbit(int x) {
		return x & -x;
	}
};

inline void solve() {

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n = 1;
    cin >> n;
    while(n--) {
        solve();
    }
    return 0;
}