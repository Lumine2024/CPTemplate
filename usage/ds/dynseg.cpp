#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;

template<class Info> concept DynSegInfo = requires(Info a, Info b, ll l, ll r) {
	Info{};
	Info(l, r);
	{ a + b } -> same_as<Info>;
	{ a.apply(b) } -> same_as<void>;
	{ a.l } -> convertible_to<ll>;
	{ a.r } -> convertible_to<ll>;
	{ a.ls } -> convertible_to<ll>;
	{ a.rs } -> convertible_to<ll>;
};

template<DynSegInfo Info> struct DynSegTree {
	explicit DynSegTree(ll _n) : n(_n), info(1, Info(0, _n)) {}
	void update(ll x, const Info &src) {
		_update(x, src, 0);
	}
	Info query(ll l, ll r) const {
		return _query(l, r, 0);
	}
private:
	vector<Info> info;
	ll n;
	void _update(ll x, const Info &src, ll u) {
		if(info[u].l == info[u].r - 1) {
			src.apply(info[u]);
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
		ll _l = info[u].l, _r = info[u].r, _ls = info[u].ls, _rs = info[u].rs;
		info[u] = Info{};
		if(_ls != -1) info[u] = info[u] + info[_ls];
		if(_rs != -1) info[u] = info[u] + info[_rs];
		info[u].l = _l; info[u].r = _r; info[u].ls = _ls; info[u].rs = _rs;
	}
	Info _query(ll ql, ll qr, ll u) const {
		if(ql <= info[u].l && qr >= info[u].r) return info[u];
		Info ret{};
		ll mid = (info[u].l + info[u].r) / 2;
		if(ql < mid && info[u].ls != -1) ret = ret + _query(ql, qr, info[u].ls);
		if(qr > mid && info[u].rs != -1) ret = ret + _query(ql, qr, info[u].rs);
		return ret;
	}
};

struct Info {
	ll l, r, ls, rs;
	Info() : l(0), r(0), ls(-1), rs(-1) {
		
	}
	Info(ll _l, ll _r) : l(_l), r(_r), ls(-1), rs(-1) {
		
	}
	Info operator+(const Info &i) const {
		Info ret{};

		return ret;
	}
	void apply(Info &dst) const {

	}
};

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