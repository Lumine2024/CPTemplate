#include "../common.h"

// 操作后，graph就变成了最短路
void floyd(vector<vector<ll>> &graph) {
	for(int k = 0; k < graph.size(); ++k) {
		for(int i = 0; i < graph.size(); ++i) {
			for(int j = 0; j < graph.size(); ++j) {
				chkmin(graph[i][j], graph[i][k] + graph[k][j]);
			}
		}
	}
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
