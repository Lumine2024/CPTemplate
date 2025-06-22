#pragma once
#include <bits/stdc++.h>
#include "DataStructures/FenwickTree.hpp"
using namespace std;
using ll = long long;
using ull = unsigned long long;

struct Data {
	int x, y, z;
	int cnt;
	int ans;
	Data(int x_, int y_, int z_) :x(x_), y(y_), z(z_), cnt(1), ans(-1) {}
};
inline void cdq_partition(int n, int k, vector<Data> &_datas) noexcept {
	Fenwick fwk(k);
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
	for(int i : ans) {
		cout << i << '\n';
	}
}