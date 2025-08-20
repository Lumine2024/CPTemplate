// Standalone C++ file generated from ds/cdq.hpp
// Can be directly submitted to online judges

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;

inline constexpr ll inf = 0x3f3f3f3f3f3f3f3f;
inline constexpr int maxn = 100005, infint = 0x3f3f3f3f;
inline constexpr ld eps = 1e-9l, infld = 1e12l;

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

// === ds/fenwick.hpp (Fenwick tree needed for CDQ) ===
template<class T> struct Fenwick {
	explicit Fenwick(int n) : tree(n + 1, 0), n(n) {}
	void update(int i, T delta) {
		++i;
		for(; i <= n; i += i & -i) {
			tree[i] += delta;
		}
	}
	T query(int i) const {
		++i;
		T sum = 0;
		for(; i > 0; i -= i & -i) {
			sum += tree[i];
		}
		return sum;
	}
	T query(int l, int r) const {
		return query(r) - query(l - 1);
	}
private:
	vector<T> tree;
	int n;
};

// === ds/cdq.hpp ===

struct Data {
	int x, y, z;
	int cnt;
	int ans;
	Data(int x_, int y_, int z_) : x(x_), y(y_), z(z_), cnt(1), ans(-1) {}
};
vector<int> threed_partial(int n, int k, vector<Data> &_datas) {
	Fenwick<int> fwk(k);
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
		if((_datas[i].x != _datas[i + 1].x) ||
			(_datas[i].y != _datas[i + 1].y) ||
			(_datas[i].z != _datas[i + 1].z)) {
			datas.emplace_back(_datas[i].x, _datas[i].y, _datas[i].z);
			cnt = 0;
			}
	}
	int m = datas.size();
	auto cdq = [&](auto &&cdq, int l, int r) -> void {
		if(r - l < 2) {
			return;
		}
		int mid = (l + r) >> 1;
		cdq(cdq, l, mid);
		cdq(cdq, mid, r);
		sort(datas.begin() + l, datas.begin() + mid, [](const Data &l, const Data &r) {
			if(l.y != r.y) return l.y < r.y;
			return l.z < r.z;
		});
		sort(datas.begin() + mid, datas.begin() + r, [](const Data &l, const Data &r) {
			if(l.y != r.y) return l.y < r.y;
			return l.z < r.z;
		});
		int j = l;
		for(int i = mid; i < r; ++i) {
			while(datas[j].y <= datas[i].y && j < mid) {
				fwk.update(datas[j].z, datas[j].cnt);
				++j;
			}
			datas[i].ans += fwk.query(datas[i].z);
		}
		for(int k = l; k < j; ++k) {
			fwk.update(datas[k].z, -datas[k].cnt);
		}
	};
	cdq(cdq, 0, m);
	vector<int> ans(n, 0);
	for(int i = 0; i < m; ++i) {
		ans[datas[i].ans + datas[i].cnt - 1] += datas[i].cnt;
	}
	return ans;
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
