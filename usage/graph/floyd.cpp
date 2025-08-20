
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;


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
