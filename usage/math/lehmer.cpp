
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;

inline constexpr int maxn = 100005, infint = 0x3f3f3f3f;

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
