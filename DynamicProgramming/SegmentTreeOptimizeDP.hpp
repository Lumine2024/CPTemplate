#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

struct SegTree {
    const int n;
    SegTree(int sz) : n(sz), s(sz * 4, 0) {}

    ll query(int l, int r) {
        if (l >= r) return 0;
        return _q(l, r, 0, 0, n);
    }

    void update(int x, ll v) {
        _u(x, v, 0, 0, n);
    }

private:
    vector<ll> s;
    ll _q(int ql, int qr, int r, int rl, int rr) {
        if (ql <= rl && qr >= rr) return s[r];
        int m = (rl + rr) / 2;
        ll ret = 0;
        if (ql < m) ret = max(ret, _q(ql, qr, r * 2 + 1, rl, m));
        if (qr > m) ret = max(ret, _q(ql, qr, r * 2 + 2, m, rr));
        return ret;
    }

    void _u(int x, ll v, int r, int rl, int rr) {
        if (rl == rr - 1) {
            s[r] = max(s[r], v);
            return;
        }
        int m = (rl + rr) / 2;
        if (x < m) {
            _u(x, v, r * 2 + 1, rl, m);
        } else {
            _u(x, v, r * 2 + 2, m, rr);
        }
        s[r] = max(s[r * 2 + 1], s[r * 2 + 2]);
    }
};

// SegTree区间最大值、单点加法线段树
int lis(const vector<int> &nums) {
	auto discrete = nums;
	sort(discrete.begin(), discrete.end());
	discrete.erase(unique(discrete.begin(), discrete.end()), discrete.end());
	unordered_map<int, int> mp;
	for(int i = 0; i < discrete.size(); i++) {
		mp[discrete[i]] = i;
	}
	SegTree seg(discrete.size());
	for(int i = 0; i < nums.size(); i++) {
		int x = mp[nums[i]];
		int v = seg.query(0, x) + 1;
		seg.update(x, v);
	}
	return seg.query(0, discrete.size());
}