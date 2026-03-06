#include "common.h"

struct DSU {
	explicit DSU(int n) : fs(n, -1) {}
	int find(int x) {
		if(fs[x] < 0) return x;
		return fs[x] = find(fs[x]);
	}
	bool is_connected(int x, int y) {
		return find(x) == find(y);
	}
	int size(int x) {
		return -fs[find(x)];
	}
	void connect(int x, int y) {
		x = find(x);
		y = find(y);
		if(x == y) return;
		int sx = size(x), sy = size(y);
		if(sx < sy) {
			fs[y] -= sx;
			fs[x] = y;
		} else {
			fs[x] -= sy;
			fs[y] = x;
		}
	}

private:
	vector<int> fs; // fa or size
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
