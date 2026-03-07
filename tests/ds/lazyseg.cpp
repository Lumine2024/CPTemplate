#include "lazyseg.h"
#include "../test.h"

struct RangeSumInfo {
	ll sum = 0;
	ll cnt = 0;
	RangeSumInfo() = default;
	RangeSumInfo(ll s, ll c) : sum(s), cnt(c) {}
	RangeSumInfo operator+(const RangeSumInfo &o) const {
		return {sum + o.sum, cnt + o.cnt};
	}
};

struct AddTag {
	ll add = 0;
	AddTag() = default;
	explicit AddTag(ll v) : add(v) {}
	bool empty() const { return add == 0; }
	void clear() { add = 0; }
	void apply(RangeSumInfo &x, int /*l*/, int /*r*/) const { x.sum += add * x.cnt; }
	void apply(AddTag &t, int /*l*/, int /*r*/) const { t.add += add; }
};

TEST(lazyseg_build_and_query) {
	// Build [1, 2, 3, 4, 5] with count
	vector<RangeSumInfo> v;
	for(int i = 1; i <= 5; ++i) v.push_back({i, 1});
	LazySegTree<RangeSumInfo, AddTag> seg(v);
	ENSURE(seg.query(0, 5).sum == 15);
	ENSURE(seg.query(1, 4).sum == 9);
	ENSURE(seg.query(0, 1).sum == 1);
}

TEST(lazyseg_range_update) {
	vector<RangeSumInfo> v;
	for(int i = 1; i <= 5; ++i) v.push_back({i, 1});
	LazySegTree<RangeSumInfo, AddTag> seg(v);
	// Add 10 to range [1, 3)
	seg.update(1, 3, AddTag{10});
	ENSURE(seg.query(0, 5).sum == 35);
	ENSURE(seg.query(1, 3).sum == 25);
	ENSURE(seg.query(0, 1).sum == 1);
	ENSURE(seg.query(3, 5).sum == 9);
}

TEST(lazyseg_multiple_updates) {
	vector<RangeSumInfo> v(8, {0, 1});
	LazySegTree<RangeSumInfo, AddTag> seg(v);
	seg.update(0, 8, AddTag{1});
	ENSURE(seg.query(0, 8).sum == 8);
	seg.update(2, 5, AddTag{3});
	// positions 2,3,4 each get +3: become 4, 4, 4
	ENSURE(seg.query(2, 5).sum == 12);
	ENSURE(seg.query(0, 8).sum == 17);
}

TEST(lazyseg_assign_constructor) {
	LazySegTree<RangeSumInfo, AddTag> seg(4);
	ENSURE(seg.query(0, 4).sum == 0);
}

struct RangeMinInfo {
	ll val = (ll)2e18;
	RangeMinInfo() = default;
	explicit RangeMinInfo(ll v) : val(v) {}
	RangeMinInfo operator+(const RangeMinInfo &o) const {
		return RangeMinInfo{min(val, o.val)};
	}
};

struct AssignTag {
	ll val = (ll)2e18;
	bool assigned = false;
	AssignTag() = default;
	explicit AssignTag(ll v) : val(v), assigned(true) {}
	bool empty() const { return !assigned; }
	void clear() {
		val = (ll)2e18;
		assigned = false;
	}
	void apply(RangeMinInfo &x, int /*l*/, int /*r*/) const {
		if(assigned) x.val = val;
	}
	void apply(AssignTag &t, int /*l*/, int /*r*/) const {
		if(assigned) {
			t.val = val;
			t.assigned = true;
		}
	}
};

TEST(lazyseg_range_assign_min) {
	vector<RangeMinInfo> v;
	for(ll x : {5LL, 3LL, 8LL, 1LL, 7LL}) v.push_back(RangeMinInfo{x});
	LazySegTree<RangeMinInfo, AssignTag> seg(v);
	ENSURE(seg.query(0, 5).val == 1);
	seg.update(0, 3, AssignTag{2});
	ENSURE(seg.query(0, 3).val == 2);
	ENSURE(seg.query(0, 5).val == 1);
	seg.update(3, 5, AssignTag{4});
	ENSURE(seg.query(0, 5).val == 2);
}
