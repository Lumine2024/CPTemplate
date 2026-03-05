#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;

template<class T1, class T2, class F> bool chkf(T1 &x, const T2 &y, F &&f) {
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

template<class Info, class Applier>
concept DynSegInfo = requires(Info a, Info b, const Applier src) {
	Info{};
	Info(a);
	{ a + b } -> same_as<Info>;
	{ src.apply(a) } -> same_as<void>;
} && is_same_v<Info, typename vector<Info>::value_type>;

template<class Info, class Applier>
	requires(DynSegInfo<Info, Applier>)
struct DynSegTree {
	explicit DynSegTree(ll _n) : n(_n), info(1, _(0, _n)) {}
	void update(ll x, const Applier &src) {
		_update(x, src, 0);
	}
	Info query(ll l, ll r) const {
		return _query(l, r, 0);
	}

private:
	struct _ {
		Info info;
		ll l, r, ls, rs;
		_() : info{}, l(0), r(0), ls(-1), rs(-1) {}
		_(ll _l, ll _r) : info{}, l(_l), r(_r), ls(-1), rs(-1) {}
	};
	vector<_> info;
	ll n;
	void _update(ll x, const Applier &src, ll u) {
		if(info[u].l == info[u].r - 1) {
			src.apply(info[u].info);
			return;
		}
		ll mid = (info[u].l + info[u].r) / 2;
		if(x < mid) {
			if(info[u].ls == -1) {
				info[u].ls = info.size();
				info.emplace_back(info[u].l, mid);
			}
			_update(x, src, info[u].ls);
		} else {
			if(info[u].rs == -1) {
				info[u].rs = info.size();
				info.emplace_back(mid, info[u].r);
			}
			_update(x, src, info[u].rs);
		}
		info[u].info = Info{};
		if(info[u].ls != -1)
			info[u].info = info[u].info + info[info[u].ls].info;
		if(info[u].rs != -1)
			info[u].info = info[u].info + info[info[u].rs].info;
	}
	Info _query(ll ql, ll qr, ll u) const {
		if(ql <= info[u].l && qr >= info[u].r) return info[u].info;
		Info ret{};
		ll mid = (info[u].l + info[u].r) / 2;
		if(ql < mid && info[u].ls != -1) ret = ret + _query(ql, qr, info[u].ls);
		if(qr > mid && info[u].rs != -1) ret = ret + _query(ql, qr, info[u].rs);
		return ret;
	}
};

struct Info {

	Info() {}
	Info operator+(const Info &other) const {}
};

struct Applier {

	void apply(Info &dst) const {}
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