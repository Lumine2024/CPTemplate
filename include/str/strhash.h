#pragma once
#include "common.h"

struct StringHash {
	explicit StringHash(const string &s)
		: p1(s.size() + 1, 0), p2(s.size() + 1, 0) {
		for(int i = 0; i < (int)s.size(); ++i) {
			p1[i + 1] = (p1[i] * _s.mul1 + s[i]) % modulo;
			p2[i + 1] = p2[i] * _s.mul2 + s[i];
		}
	}
	ull substr(int l, int r) const {
		ull ret1 = (p1[r] - p1[l] * _s.pmul1[r - l] % modulo + modulo) % modulo;
		ull ret2 = p2[r] - p2[l] * _s.pmul2[r - l];
		return (ret1 << 3) ^ (ret1 >> 5) ^ ret2;
	}

private:
	vector<ull> p1, p2;
	static constexpr ull modulo = 998244353;
	static constexpr int maxn = 500005;
	struct _Statics {
		ull mul1, mul2;
		ull pmul1[maxn], pmul2[maxn];
		_Statics() {
			ull c = (ull)chrono::steady_clock::now().time_since_epoch().count();
			mul1 = c % 131 + 131;
			mul2 = c % 13331 + 13331;
			pmul1[0] = pmul2[0] = 1;
			for(int i = 1; i < maxn; ++i) {
				pmul1[i] = pmul1[i - 1] * mul1 % modulo;
				pmul2[i] = pmul2[i - 1] * mul2;
			}
		}
	};
	static inline _Statics _s;
};
