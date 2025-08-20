// Standalone C++ file generated from math/lehmer.hpp
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

// === ds/fenwick.hpp ===

// 单点
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
// 区间
struct RangeFenwick {
	const int n;
	explicit RangeFenwick(int n)
		: n(n), f1(n), f2(n) {}
	void update(int l, int r, ll v) {
		_update(l, v);
		_update(r + 1, -v);
	}
	ll query(int l, int r) const {
		return _query(r) - _query(l - 1);
	}
private:
	Fenwick f1, f2;
	void _update(int x, ll v) {
		f1.update(x, v);
		f2.update(x, v * (x - 1));
	}
	ll _query(int x) const {
		return f1.query(x) * x - f2.query(x);
	}
};

// === ds/vst.hpp ===

// value segment tree
struct VST {
	VST(int maxn) : sum((maxn + 1) * 4), n(maxn + 1) {}
	VST() : n(0) {}
	void assign(int maxn) {
		sum.assign((maxn + 1) * 4, 0);
		n = maxn + 1;
	}
	void insert(int x) {
		_update(x, 1, 0, 0, n);
	}
	void erase(int x) {
		_update(x, -1, 0, 0, n);
	}
	int qpre(int x) const {
		int rk = qrv(x);
		return qvr(rk - 1);
	}
	int qsuc(int x) const {
		int rk = qrv(x + 1);
		return qvr(rk);
	}
	int qrv(int x) const {
		return _query(0, x, 0, 0, n);
	}
	int qvr(int k) const {
		return _qvr(k, 0, 0, n);
	}
	int size() const {
		return sum[0];
	}
	int qcnt(int x) const {
		return _query(x, x + 1, 0, 0, n);
	}
	int qrange_cnt(int l, int r) const {
		return _query(l, r, 0, 0, n);
	}
private:
	vector<int> sum;
	int n;
	void _update(int x, int dv, int rt, int rl, int rr) {
		if(rr - rl == 1) {
			sum[rt] += dv;
			return;
		}
		int mid = (rl + rr) >> 1, lson = rt * 2 + 1, rson = rt * 2 + 2;
		if(x < mid) {
			_update(x, dv, lson, rl, mid);
		} else {
			_update(x, dv, rson, mid, rr);
		}
		sum[rt] = sum[lson] + sum[rson];
	}
	ll _query(int ql, int qr, int rt, int rl, int rr) const {
		if(ql <= rl && qr >= rr)
			return sum[rt];
		int mid = (rl + rr) >> 1, lson = rt * 2 + 1, rson = rt * 2 + 2;
		ll ans = 0;
		if(ql < mid) {
			ans += _query(ql, qr, lson, rl, mid);
		}
		if(qr > mid) {
			ans += _query(ql, qr, rson, mid, rr);
		}
		return ans;
	}
	int _qvr(int k, int rt, int rl, int rr) const {
		if(rr - rl == 1)
			return rl;
		int mid = (rl + rr) >> 1, lson = rt * 2 + 1, rson = rt * 2 + 2;
		if(k < sum[lson]) {
			return _qvr(k, lson, rl, mid);
		} else {
			return _qvr(k - sum[lson], rson, mid, rr);
		}
	}
};

// === math/lehmer.hpp ===

// 均为0-based排列
vector<int> lehmer(const vector<int> &a) {
	int n = a.size();
	vector<int> l(n);
	Fenwick bit(n);
	for(int i = 1; i <= n; ++i) {
		bit.update(i, 1);
	}
	for(int i = 0; i < n; ++i) {
		int x = a[i] + 1;
		l[i] = bit.query(n) - bit.query(x);
		bit.update(x, -1);
	}
	return l;
}
vector<int> rev_lehmer(const vector<int> &l) {
	int n = l.size();
	VST vst(n); // 使用权值线段树实现会快一点
	for(int i = 0; i < n; ++i) {
		vst.insert(i);
	}
	vector<int> ret(n);
	for(int i = 0; i < n; ++i) {
		ret[i] = vst.qvr(l[i] + 1);
		vst.erase(ret[i]);
	}
	return ret;
}

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
