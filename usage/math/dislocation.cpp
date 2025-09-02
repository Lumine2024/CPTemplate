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
		nums[0] = nums[1] = nums[2] = 1;
		for(ll i = 3; i < maxn; ++i) {
			nums[i] = (i - 1) * (nums[i - 1] + nums[i - 2]) % modulo;
		}
		return 0;
	}();
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