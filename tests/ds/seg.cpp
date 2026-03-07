#include "seg.h"
#include "../test.h"

struct SumInfo {
	ll val = 0;
	SumInfo() = default;
	explicit SumInfo(ll v) : val(v) {}
	SumInfo operator+(const SumInfo &o) const { return SumInfo{val + o.val}; }
};

struct SetApplier {
	ll val;
	explicit SetApplier(ll v) : val(v) {}
	void apply(SumInfo &x) const { x.val = val; }
};

TEST(seg_build_and_query) {
	vector<SumInfo> v;
	for(int i = 1; i <= 5; ++i) v.push_back(SumInfo{i});
	SegTree<SumInfo, SetApplier> seg(v);
	ENSURE(seg.query(0, 5).val == 15);
	ENSURE(seg.query(1, 4).val == 9);
	ENSURE(seg.query(0, 1).val == 1);
	ENSURE(seg.query(4, 5).val == 5);
}

TEST(seg_point_update) {
	vector<SumInfo> v;
	for(int i = 1; i <= 5; ++i) v.push_back(SumInfo{i});
	SegTree<SumInfo, SetApplier> seg(v);
	seg.update(2, SetApplier{10});
	ENSURE(seg.query(0, 5).val == 22);
	ENSURE(seg.query(2, 3).val == 10);
	ENSURE(seg.query(1, 4).val == 16);
}

TEST(seg_empty_range) {
	vector<SumInfo> v;
	for(int i = 0; i < 8; ++i) v.push_back(SumInfo{1});
	SegTree<SumInfo, SetApplier> seg(v);
	ENSURE(seg.query(3, 3).val == 0);
}

TEST(seg_assign_constructor) {
	SegTree<SumInfo, SetApplier> seg(4);
	ENSURE(seg.query(0, 4).val == 0);
	seg.update(0, SetApplier{7});
	seg.update(3, SetApplier{3});
	ENSURE(seg.query(0, 4).val == 10);
	ENSURE(seg.query(1, 3).val == 0);
}

struct MaxInfo {
	ll val = 0;
	MaxInfo() = default;
	explicit MaxInfo(ll v) : val(v) {}
	MaxInfo operator+(const MaxInfo &o) const { return MaxInfo{max(val, o.val)}; }
};

struct MaxSetApplier {
	ll val;
	explicit MaxSetApplier(ll v) : val(v) {}
	void apply(MaxInfo &x) const { x.val = val; }
};

TEST(seg_max_query) {
	vector<MaxInfo> v;
	for(ll x : {3LL, 1LL, 4LL, 1LL, 5LL, 9LL, 2LL, 6LL}) v.push_back(MaxInfo{x});
	SegTree<MaxInfo, MaxSetApplier> seg(v);
	ENSURE(seg.query(0, 8).val == 9);
	ENSURE(seg.query(0, 5).val == 5);
	ENSURE(seg.query(5, 8).val == 9);
	seg.update(5, MaxSetApplier{0});
	ENSURE(seg.query(0, 8).val == 6);
}
