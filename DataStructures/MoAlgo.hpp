#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

struct Query {
	int idx;
	// 左闭右开
	int l, r;
	int ans;
};
// 查询区间内满足元素出现次数等于自身的数的个数
void mo_algo(vector<Query> &queries, const vector<int> &nums) {
	int n = nums.size();
	int len = sqrt(n);
	sort(queries.begin(), queries.end(), [&](const Query &ql, const Query &qr) {
		int atl = ql.l / len, atr = qr.l / len;
		if(atl != atr) {
			return atl < atr;
		}
		return (bool)((atl % 2 == 0) ^ (ql.r < qr.r));
	});
	int l = 0, r = 0, ans = 0;
	vector<int> count(n + 5, 0);
	auto add = [&](int x) {
		if(x >= n + 5) return;
		if(count[x] == x) --ans;
		count[x]++;
		if(count[x] == x) ++ans;
	};
	auto remove = [&](int x) {
		if(x >= n + 5) return;
		if(count[x] == x) --ans;
		count[x]--;
		if(count[x] == x) ++ans;
	};
	for(auto &q : queries) {
		// 抄板子时注意顺序，先加再更新还是先更新再加
		while(l > q.l) {
			--l;
			add(nums[l]);
		}
		while(l < q.l) {
			remove(nums[l]);
			++l;
		}
		while(r < q.r) {
			add(nums[r]);
			++r;
		}
		while(r > q.r) {
			--r;
			remove(nums[r]);
		}
		q.ans = ans;
	}
	sort(queries.begin(), queries.end(), [](const Query &l, const Query &r) {
		return l.idx < r.idx;
	});
}