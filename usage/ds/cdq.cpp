#include "common.h"

template<class T>
concept FenwickInfo = requires(T a, T b) {
	{ a + b } -> convertible_to<T>;
};
template<FenwickInfo T> struct Fenwick {
	explicit Fenwick(int n) : _nums(n + 1, 0), _n(n) {}
	T query(int x) const {
		T ans{};
		for(; x; x -= x & -x) ans = ans + _nums[x];
		return ans;
	}
	void update(int x, const T &v) {
		for(; x <= _n; x += x & -x) _nums[x] = _nums[x] + v;
	}

private:
	vector<T> _nums;
	int _n;
};

struct Data {
	int x, y, z, cnt, ans;
	Data(int x_, int y_, int z_) : x(x_), y(y_), z(z_), cnt(1), ans(-1) {}
};
vector<int> threed_partial(int n, int k, vector<Data> _datas) {
	Fenwick<int> f(k);
	sort(_datas.begin(), _datas.end() - 1, [](const Data &l, const Data &r) {
		if(l.x != r.x) return l.x < r.x;
		if(l.y != r.y) return l.y < r.y;
		return l.z < r.z;
	});
	// 如果值域很大，考虑离散化数据
	vector<Data> datas;
	datas.reserve(n);
	int cnt = 0;
	for(int i = 0; i < n; ++i) {
		++cnt;
		if((i == n - 1) || (_datas[i].x != _datas[i + 1].x) ||
		   (_datas[i].y != _datas[i + 1].y) ||
		   (_datas[i].z != _datas[i + 1].z)) {
			datas.emplace_back(_datas[i].x, _datas[i].y, _datas[i].z).cnt = cnt;
			cnt = 0;
		}
	}
	int m = datas.size();
	auto cdq = [&](auto &&cdq, int l, int r) -> void {
		if(r - l < 2) return;
		int mid = (l + r) / 2;
		cdq(cdq, l, mid);
		cdq(cdq, mid, r);
		sort(datas.begin() + l, datas.begin() + mid,
			 [](const Data &l, const Data &r) {
				 if(l.y != r.y) return l.y < r.y;
				 return l.z < r.z;
			 });
		sort(datas.begin() + mid, datas.begin() + r,
			 [](const Data &l, const Data &r) {
				 if(l.y != r.y) return l.y < r.y;
				 return l.z < r.z;
			 });
		int j = l;
		for(int i = mid; i < r; ++i) {
			while(datas[j].y <= datas[i].y && j < mid) {
				f.update(datas[j].z, datas[j].cnt);
				++j;
			}
			datas[i].ans += f.query(datas[i].z);
		}
		for(int k = l; k < j; ++k) f.update(datas[k].z, -datas[k].cnt);
	};
	cdq(cdq, 0, m);
	vector<int> ans(n, 0);
	for(int i = 0; i < m; ++i) {
		ans[datas[i].ans + datas[i].cnt - 1] += datas[i].cnt;
	}
	return ans;
}

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
