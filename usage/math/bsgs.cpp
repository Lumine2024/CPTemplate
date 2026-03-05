#include "../common.h"

constexpr ll modulo = 998244353;
inline ll qpow(ll x, ll n) {
	ll ret = 1;
	for(; n; n >>= 1, x = x * x % modulo)
		if(n & 1) ret = ret * x % modulo;
	return ret;
}

struct MyHash {
	size_t operator()(ll _x) const noexcept {
		ull x = _x;
		x ^= c;
		x ^= (x >> 21);
		x ^= (x << 37);
		x ^= (x >> 4);
		x *= 0x27d4eb2f165667c5;
		x *= c;
		x ^= (x >> 28);
		x *= 0x165667b19e3779f9;
		x ^= (x >> 31);
		return x ^ c;
	}

private:
	static inline const size_t c =
		(size_t)chrono::steady_clock::now().time_since_epoch().count();
};

// returns ret so that qpow(ret, a) = b, -1 if not exist
ll mlog(ll a, ll b) {
	if(b == 1) return 0;
	ll t = ceil(sqrt(modulo));
	ll now = b;
	unordered_map<ll, ll, MyHash>
		table; // Hey, I used std::unordered_map! Hack it!
	for(int i = 0; i < t; ++i) {
		table[now] = i;
		now = now * a % modulo;
	}
	ll mi = qpow(a, t);
	now = 1;
	for(int i = 1; i <= t; ++i) {
		now = now * mi % modulo;
		if(table.contains(now)) {
			return i * t - table[now];
		}
	}
	return -1;
}

inline void solve() {}

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