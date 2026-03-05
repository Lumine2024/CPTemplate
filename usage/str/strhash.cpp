#include "../common.h"

struct StringHash {
	explicit StringHash(const string &s)
		: p1(s.size() + 1, 0), p2(s.size() + 1, 0) {
		for(int i = 0; i < s.size(); ++i) {
			p1[i + 1] = (p1[i] * mul1 + s[i]) % modulo;
			p2[i + 1] = p2[i] * mul2 + s[i];
		}
	}
	ull substr(int l, int r) const {
		ull ret1 = (p1[r] - p1[l] * pmul1[r - l] % modulo + modulo) % modulo;
		ull ret2 = p2[r] - p2[l] * pmul2[r - l];
		return (ret1 << 3) ^ (ret1 >> 5) ^ ret2;
	}

private:
	vector<ull> p1, p2;
	static inline const ull c =
		(ull)chrono::steady_clock::now().time_since_epoch().count();
	static inline const ull mul1 = c % 131 + 131, mul2 = c % 13331 + 13331;
	static constexpr ull modulo = 998244353, maxn = 500005;
	static inline ull pmul1[maxn], pmul2[maxn];
	static inline int init = [] {
		pmul1[0] = pmul2[0] = 1;
		for(int i = 1; i < maxn; ++i) {
			pmul1[i] = pmul1[i - 1] * mul1 % modulo;
			pmul2[i] = pmul2[i - 1] * mul2;
		}
		return 0;
	}();
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
