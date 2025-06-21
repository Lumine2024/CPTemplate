#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

// 单调栈：[l, r)，且有相同元素时，左边取最左端，右边取下一个自己
vector<pair<int, int>> max_range_1(const vector<int> &nums) {
	int n = nums.size();
	vector ret(n, pair(-1, -1));
	vector<pair<int, int>> stk; // 单调栈
	ret[0].first = 0;
	stk.emplace_back(nums[0], 0);
	for(int i = 1; i < n; ++i) {
		while(!stk.empty() && stk.back().first <= nums[i]) {
			ret[stk.back().second].second = i;
			stk.pop_back();
		}
		ret[i].first = stk.empty() ? 0 : stk.back().second + 1;
		stk.emplace_back(nums[i], i);
	}
	for(int i = n - 1; i >= 0; --i) {
		if(ret[i].second == -1) {
			ret[i].second = n;
		}
	}
	return ret;
}
// 可以有相同元素
vector<pair<int, int>> max_range_2(const vector<int> &nums) {
	int n = nums.size();
	vector ret(n, pair(0, n));
	vector<int> stk;
	for(int i = 0; i < n; ++i) {
		while(!stk.empty() && nums[stk.back()] <= nums[i]) {
			stk.pop_back();
		}
		if(!stk.empty()) {
			ret[i].first = stk.back() + 1;
		}
		stk.push_back(i);
	}
	stk.clear();
	for(int i = n - 1; i >= 0; --i) {
		while(!stk.empty() && nums[stk.back()] <= nums[i]) {
			stk.pop_back();
		}
		if(!stk.empty()) {
			ret[i].second = stk.back();
		}
		stk.push_back(i);
	}
	return ret;
}
// 最大滑动窗口：单调队列
vector<int> max_sliding_window(const vector<int> &nums, int k) {
	int n = nums.size();
	vector<int> ret(n - k + 1);
	vector<pair<int, int>> que;
	for(int i = 0; i < k - 1; ++i) {
		while(!que.empty() && que.back().first < nums[i]) {
			que.pop_back();
		}
		que.emplace_back(nums[i], i);
	}
	int st = 0;
	for(int i = 0; i <= n - k; ++i) {
		int j = i + k - 1;
		if(que.size() > st && que[st].second < i) {
			++st;
		}
		while(!que.empty() && que.back().first < nums[j]) {
			que.pop_back();
		}
		st = min(st, (int)que.size());
		que.emplace_back(nums[j], j);
		ret[i] = que[st].first;
	}
	return ret;
}