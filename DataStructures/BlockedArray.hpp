#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

struct Block {
	Block() : l(-1), r(-1) {}
	// 注意左闭右开
	Block(int l, int r, const vector<ll> &nums_)
		: nums(r - l), lazy(0), sum(0), l(l), r(r) {
		for(int i = l; i < r; ++i) {
			nums[i - l] = nums_[i];
			sum += nums[i - l];
		}
	}
	// 注意左闭右开
	void update(int ul, int ur, ll dval) {
		if(ul > r || ur < l) {
			return;
		}
		if(ul <= l && ur >= r) {
			lazy += dval;
			sum += dval * (r - l);
			return;
		}
		for(int i = max(ul, l); i < min(ur, r); ++i) {
			nums[i - l] += dval;
		}
		sum += dval * (min(ur, r) - max(ul, l));
	}
	// 注意左闭右开
	ll query(int ql, int qr) const {
		if(ql >= r || qr <= l) {
			return 0;
		}
		if(ql <= l && qr >= r) {
			return sum;
		}
		ll ans = lazy * (min(qr, r) - max(ql, l));
		for(int i = max(ql, l); i < min(qr, r); ++i) {
			ans += nums[i - l];
		}
		return ans;
	}
private:
	vector<ll> nums;
	ll lazy;
	ll sum;
	int l, r;
};
struct BlockedArray {
	BlockedArray(const vector<ll> &nums) {
		int r = nums.size();
		int len = sqrt(r + 0.5);
		int size = (r + len - 1) / len;
		blocks.reserve(size);
		for(int i = 0; i < size; ++i) {
			int ll = i * len, rr = min((i + 1) * len, r);
			blocks.emplace_back(ll, rr, nums);
		}
	}
	void update(int l, int r, ll d) {
		for(auto &blk : blocks) {
			blk.update(l, r, d);
		}
	}
	ll query(int l, int r) const {
		ll ans = 0;
		for(const auto &blk : blocks) {
			ans += blk.query(l, r);
		}
		return ans;
	}
private:
	vector<Block> blocks;
};