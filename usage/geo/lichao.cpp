#include "geo/basic.h"

struct LiChao {
	vector<Lineseg> lines;
	explicit LiChao(int ma) : id(ma * 4, -1), n(ma) {}
	void addline(int x1, int x2, int y1, int y2) {
		Lineseg ls({ld(x1), ld(y1)}, {ld(x2), ld(y2)});
		int i = lines.size();
		lines.push_back(ls);
		_update(i, min(x1, x2), max(x1, x2), 0, 0, n - 1);
	}
	int query(int k) const {
		return _query(k, 0, 0, n - 1).second;
	}

private:
	vector<int> id;
	int n;
	static pair<ld, int> _max(const pair<ld, int> &a, const pair<ld, int> &b) {
		int cmp1 = cmp(a.first, b.first);
		if(cmp1 != 0) return (cmp1 == 1) ? a : b;
		return a.second < b.second ? a : b;
	}
	void _update(int i, int ul, int ur, int u, int rl, int rr) {
		int mid = (rl + rr) / 2, ls = u * 2 + 1, rs = u * 2 + 2;
		if(ul <= rl && ur >= rr) {
			if(id[u] == -1) {
				id[u] = i;
				return;
			}
			if(cmp(lines[i].at(mid), lines[id[u]].at(mid)) == 1) swap(i, id[u]);
			if(cmp(lines[i].at(rl), lines[id[u]].at(rl)) == 1)
				_update(i, ul, ur, ls, rl, mid);
			if(cmp(lines[i].at(rr), lines[id[u]].at(rr)) == 1)
				_update(i, ul, ur, rs, mid + 1, rr);
		} else {
			if(ul <= mid) _update(i, ul, ur, ls, rl, mid);
			if(mid < ur) _update(i, ul, ur, rs, mid + 1, rr);
		}
	}
	pair<ld, int> _query(int k, int u, int rl, int rr) const {
		pair<ld, int> ret(-inf, -1);
		if(id[u] != -1) ret = {lines[id[u]].at(k), id[u]};
		if(rl == rr) return ret;
		int mid = (rl + rr) / 2, ls = u * 2 + 1, rs = u * 2 + 2;
		if(k <= mid) ret = _max(ret, _query(k, ls, rl, mid));
		else ret = _max(ret, _query(k, rs, mid + 1, rr));
		return ret;
	}
};

inline void solve() {}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int n = 1;
	// cin >> n;
	while(n--) {
		solve();
	}
	return 0;
}