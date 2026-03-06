#include "common.h"

template<class Info, class Applier>
concept SegInfo = requires(Info a, Info b, const Applier src) {
	Info{};
	Info(a);
	{ a + b } -> same_as<Info>;
	{ src.apply(a) } -> same_as<void>;
} && is_same_v<Info, typename vector<Info>::value_type>;

template<class Info, class Applier>
	requires(SegInfo<Info, Applier>)
struct SegTree {
	SegTree() : n(0) {}
	explicit SegTree(int sz) : n(sz), info(sz * 4, Info()) {}
	explicit SegTree(const vector<Info> &v) : n(v.size()), info(v.size() * 4) {
		_build(v, 0, 0, n);
	}
	void assign(int sz) {
		n = sz;
		info.assign(n * 4, Info());
	}
	void assign(const vector<Info> &v) {
		n = v.size();
		info.assign(n * 4, Info());
		_build(v, 0, 0, n);
	}
	Info query(int l, int r) const {
		if(l == r) return Info();
		return _query(l, r, 0, 0, n);
	}
	void update(int x, const Applier &v) {
		_update(x, v, 0, 0, n);
	}

private:
	int n;
	vector<Info> info;
	void _build(const vector<Info> &v, int u, int rl, int rr) {
		if(rl == rr - 1) {
			info[u] = v[rl];
			return;
		}
		int mid = (rl + rr) / 2, ls = u * 2 + 1, rs = u * 2 + 2;
		_build(v, ls, rl, mid);
		_build(v, rs, mid, rr);
		info[u] = info[ls] + info[rs];
	}
	Info _query(int ql, int qr, int u, int rl, int rr) const {
		if(ql <= rl && qr >= rr) return info[u];
		int mid = (rl + rr) / 2, ls = u * 2 + 1, rs = u * 2 + 2;
		Info ret{};
		if(ql < mid) ret = ret + _query(ql, qr, ls, rl, mid);
		if(qr > mid) ret = ret + _query(ql, qr, rs, mid, rr);
		return ret;
	}
	void _update(int x, const Applier &v, int u, int rl, int rr) {
		if(rl == rr - 1) {
			v.apply(info[u]);
			return;
		}
		int mid = (rl + rr) >> 1, ls = u * 2 + 1, rs = u * 2 + 2;
		if(x < mid) _update(x, v, ls, rl, mid);
		else _update(x, v, rs, mid, rr);
		info[u] = info[ls] + info[rs];
	}
};

struct Info {

	Info() {}
	Info operator+(const Info &i) const {}
};

struct Applier {

	void apply(Info &x) const {}
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
