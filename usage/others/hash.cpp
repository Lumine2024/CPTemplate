#include "common.h"

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

inline void solve() {}

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
