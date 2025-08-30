
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;

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

struct ACAM {
	ACAM() : nodes(1) {}
	void insert(const string &str) {
		int now = 0;
		for(char ch : str) {
			int id = ch - 'a';
			int v = nodes[now].nxt1[id];
			if(v == -1) {
				v = nodes[now].nxt1[id] = nodes[now].nxt2[id] = nodes.size();
				nodes.emplace_back();
			}
			now = v;
		}
		nodes[now].cnt++;
	}
	void build() {
		queue<int> q;
		nodes[0].fail = 0;
		for(int i = 0; i < 26; ++i) {
			int v = nodes[0].nxt2[i];
			if(v == -1) {
				nodes[0].nxt2[i] = 0;
			} else {
				nodes[v].fail = 0;
				q.push(v);
			}
		}
		while(!q.empty()) {
			int now = q.front();
			q.pop();
			for(int i = 0; i < 26; ++i) {
				int v = nodes[now].nxt2[i];
				if(v == -1) {
					nodes[now].nxt2[i] = nodes[nodes[now].fail].nxt2[i];
				} else {
					nodes[v].fail = nodes[nodes[now].fail].nxt2[i];
					q.push(v);
				}
			}
		}
		q.push(0);
		while(!q.empty()) {
			int u = q.front();
			q.pop();
			for(int i = 0; i < 26; ++i) {
				int v = nodes[u].nxt1[i];
				if(v == -1) {
					continue;
				}
				q.push(v);
				int fu = nodes[u].fail;
				if(fu != 0 && nodes[fu].cnt == 0) {
					nodes[u].fail = nodes[fu].fail;
				}
			}
		}
	}
	int find(const string &s) const {
		int now = 0;
		for(char ch : s) {
			int v = nodes[now].nxt1[ch - 'a'];
			if(v == -1) {
				return -1;
			}
			now = v;
		}
		return now;
	}
	vector<int> query(const string &str) const {
		int now = 0;
		vector<int> ret(nodes.size(), 0);
		for(char ch : str) {
			int id = ch - 'a';
			now = nodes[now].nxt2[id];
			int u = now;
			while(u != 0) {
				ret[u]++;
				u = nodes[u].fail;
			}
		}
		return ret;
	}
	int size() const {
		return nodes.size();
	}
private:
	struct Node {
		int cnt;
		int fail;
		array<int, 26> nxt1, nxt2;
		Node() : cnt(0), fail(0) {
			nxt1.fill(-1);
			nxt2.fill(-1);
		}
	};
	vector<Node> nodes;
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
