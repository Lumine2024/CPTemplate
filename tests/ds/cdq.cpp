#include "ds/cdq.h"
#include "ds/fenwick.h"
#include "../test.h"

struct ThreeDPartialOrderInfo {
	int x, y, z, cnt, ans;
};

struct ThreeDPartialOrderSolver : public CdqBase<ThreeDPartialOrderInfo> {
	explicit ThreeDPartialOrderSolver(vector<ThreeDPartialOrderInfo> v, int k)
		: CdqBase(), n(static_cast<int>(v.size())), f(k) {
		sort(v.begin(), v.end(),
			 [](const ThreeDPartialOrderInfo &l,
				const ThreeDPartialOrderInfo &r) {
				 if(l.x != r.x) return l.x < r.x;
				 if(l.y != r.y) return l.y < r.y;
				 return l.z < r.z;
			 });
		infos.reserve(v.size());
		int cnt = 0;
		for(int i = 0; i < n; ++i) {
			++cnt;
			if((i == n - 1) || (v[i].x != v[i + 1].x) ||
			   (v[i].y != v[i + 1].y) || (v[i].z != v[i + 1].z)) {
				infos.push_back({v[i].x, v[i].y, v[i].z, cnt, 0});
				cnt = 0;
			}
		}
		m = infos.size();
	}
	void solve_cross(int l, int m, int r) override {}
	void merge(int l, int m, int r) override {
		sort(infos.begin() + l, infos.begin() + m,
			 [](const ThreeDPartialOrderInfo &l,
				const ThreeDPartialOrderInfo &r) {
				 if(l.y != r.y) return l.y < r.y;
				 return l.z < r.z;
			 });
		sort(infos.begin() + m, infos.begin() + r,
			 [](const ThreeDPartialOrderInfo &l,
				const ThreeDPartialOrderInfo &r) {
				 if(l.y != r.y) return l.y < r.y;
				 return l.z < r.z;
			 });
		int j = l;
		for(int i = m; i < r; ++i) {
			while(j < m && infos[j].y <= infos[i].y) {
				f.update(infos[j].z, infos[j].cnt);
				++j;
			}
			infos[i].ans += f.query(infos[i].z);
		}
		for(int k = l; k < j; ++k) {
			f.update(infos[k].z, -infos[k].cnt);
		}
	}
	vector<int> histogram() const {
		vector<int> ans(n, 0);
		for(const auto &info : infos) {
			ans[info.ans + info.cnt - 1] += info.cnt;
		}
		return ans;
	}
	void run_and_check() {
		run();
	}

private:
	int n, m;
	Fenwick<int> f;
};

static vector<int> brute_histogram(const vector<ThreeDPartialOrderInfo> &pts) {
	vector<int> hist(pts.size(), 0);
	for(size_t i = 0; i < pts.size(); ++i) {
		int dominated = 0;
		for(size_t j = 0; j < pts.size(); ++j) {
			if(pts[j].x <= pts[i].x && pts[j].y <= pts[i].y &&
			   pts[j].z <= pts[i].z) {
				++dominated;
			}
		}
		hist[dominated - 1]++;
	}
	return hist;
}

static void
expect_histogram_matches_bruteforce(const vector<ThreeDPartialOrderInfo> &pts,
									int k) {
	ThreeDPartialOrderSolver solver(pts, k);
	solver.run_and_check();
	ENSURE(solver.histogram() == brute_histogram(pts));
}

TEST(cdq_single_point) {
	vector<ThreeDPartialOrderInfo> pts = {{1, 1, 1, 1, 0}};
	expect_histogram_matches_bruteforce(pts, 1);
}

TEST(cdq_all_duplicates) {
	vector<ThreeDPartialOrderInfo> pts = {
		{2, 2, 2, 1, 0}, {2, 2, 2, 1, 0}, {2, 2, 2, 1, 0}};
	expect_histogram_matches_bruteforce(pts, 2);
	ENSURE(brute_histogram(pts) == vector<int>({0, 0, 3}));
}

TEST(cdq_mixed_small_case) {
	vector<ThreeDPartialOrderInfo> pts = {{1, 1, 1, 1, 0}, {1, 2, 1, 1, 0},
										  {2, 1, 2, 1, 0}, {2, 2, 2, 1, 0},
										  {2, 2, 2, 1, 0}, {3, 3, 1, 1, 0}};
	expect_histogram_matches_bruteforce(pts, 3);
}

TEST(cdq_randomized_against_bruteforce) {
	mt19937 rng(20260331);
	uniform_int_distribution<int> coord(1, 5);
	for(int n = 1; n <= 8; ++n) {
		for(int tc = 0; tc < 40; ++tc) {
			vector<ThreeDPartialOrderInfo> pts;
			pts.reserve(n);
			for(int i = 0; i < n; ++i) {
				pts.push_back({coord(rng), coord(rng), coord(rng), 1, 0});
			}
			expect_histogram_matches_bruteforce(pts, 5);
		}
	}
}