#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

pair<int, stack<int>> iddfs(array<array<int, 3>, 3> src, const array<array<int, 3>, 3> &dst) {
	constexpr int dx[] = { -1, 1, 0, 0 };
	constexpr int dy[] = { 0, 0, -1, 1 };
	int ans = 0;
	stack<int> stk;
	pair<int, int> zeropos;
	for(int i = 0; i < 3; ++i) {
		for(int j = 0; j < 3; ++j) {
			if(src[i][j] == 0) {
				zeropos = { i, j };
			}
		}
	}
	auto dfs = [&](auto &&dfs, int depth, int lastdir) -> bool {
		if(src == dst) {
			for(int i = 0; i < 3; ++i) {
				for(int j = 0; j < 3; ++j) {
					stk.push(src[i][j]);
				}
			}
			return true;
		}
		if(depth >= ans) return false;
		auto revdir = [](int cur) -> int {
			if(cur < 2) return 1 - cur;
			return 5 - cur;
		};
		for(int nowdir = 0; nowdir < 4; ++nowdir) {
			if(nowdir == revdir(lastdir)) {
				continue;
			}
			auto [oldx, oldy] = zeropos;
			int newx = oldx + dx[nowdir], newy = oldy + dy[nowdir];
			if(newx < 0 || newx > 2 || newy < 0 || newy > 2) continue;
			swap(src[oldx][oldy], src[newx][newy]);
			zeropos = { newx, newy };
			if(dfs(dfs, depth + 1, nowdir)) {
				swap(src[oldx][oldy], src[newx][newy]);
				zeropos = { oldx, oldy };
				for(int i = 0; i < 3; ++i) {
					for(int j = 0; j < 3; ++j) {
						stk.push(src[i][j]);
					}
				}
				return true;
			}
			swap(src[oldx][oldy], src[newx][newy]);
			zeropos = { oldx, oldy };
		}
		return false;
	};
	for(ans = 0; ans < 33; ++ans) {
		if(dfs(dfs, 0, 114514)) {
			return { ans, stk };
		}
	}
	return { -1, stack<int>{} };
}