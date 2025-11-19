
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

struct Trie {
	Trie() : nodes(1) {}
	void insert(const string &str) {
		int rt = 0;
		for(int i = 0; i < str.size(); ++i) {
			if((nodes[rt].nxt[getnum(str[i])]) == -1) {
				nodes[rt].nxt[getnum(str[i])] = nodes.size();
				nodes.emplace_back();
			}
			nodes[rt].cnt++;
			rt = nodes[rt].nxt[getnum(str[i])];
		}
		nodes[rt].cnt++;
		nodes[rt].end = true;
	}
	bool find(const string &str) const {
		int rt = 0;
		for(int i = 0; i < str.size(); ++i) {
			if((nodes[rt].nxt[getnum(str[i])]) == -1) {
				return false;
			}
			rt = nodes[rt].nxt[getnum(str[i])];
		}
		return nodes[rt].end;
	}
	int prefix_count(const string &str) const {
		int rt = 0;
		for(int i = 0; i < str.size(); ++i) {
			if((nodes[rt].nxt[getnum(str[i])]) == -1) {
				return 0;
			}
			rt = nodes[rt].nxt[getnum(str[i])];
		}
		return nodes[rt].cnt;
	}
private:
	struct Node {
		array<int, 65> nxt;
		bool end;
		int cnt;
		Node() : end(false), cnt(0) {
			nxt.fill(-1);
		}
	};
	vector<Node> nodes;
	static int getnum(char x) {
		if(x >= 'A' && x <= 'Z') return x - 'A';
		else if(x >= 'a' && x <= 'z') return x - 'a' + 26;
		else return x - '0' + 52;
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
