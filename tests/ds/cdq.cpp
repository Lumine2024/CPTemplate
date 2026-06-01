#include "ds/cdq.h"
#include "ds/fenwick.h"
#include "doctest.h"

struct ThreeDPartialOrderInfo {
	int x, y, z, cnt, ans;
};

struct ThreeDPartialOrderSolver : public CdqBase {
	explicit ThreeDPartialOrderSolver(vector<ThreeDPartialOrderInfo> v, int k)
		: total_points(static_cast<int>(v.size())), f(k) {
		sort(v.begin(), v.end(), by_xyz);
		infos.reserve(v.size());
		for(int i = 0; i < total_points;) {
			int j = i + 1;
			while(j < total_points && same_point(v[i], v[j])) {
				++j;
			}
			infos.push_back({v[i].x, v[i].y, v[i].z, j - i, 0});
			i = j;
		}
		n = static_cast<int>(infos.size());
		buffer.resize(n);
	}
	void solve_cross(int l, int m, int r) override {
		vector<ThreeDPartialOrderInfo> right(infos.begin() + m, infos.begin() + r);
		sort(right.begin(), right.end(), by_yz);
		int i = l;
		for(auto &info : right) {
			while(i < m && compare_yz(infos[i], info) <= 0) {
				f.update(infos[i].z, infos[i].cnt);
				++i;
			}
			info.ans += f.query(info.z);
		}
		for(int j = l; j < i; ++j) {
			f.update(infos[j].z, -infos[j].cnt);
		}
		sort(right.begin(), right.end(), by_xyz);
		for(int j = m; j < r; ++j) {
			infos[j].ans = right[j - m].ans;
		}
	}
	void merge(int l, int m, int r) override {
		int i = l;
		int j = m;
		int p = l;
		while(i < m || j < r) {
			if(j == r || (i < m && by_yz(infos[i], infos[j]))) {
				buffer[p++] = infos[i++];
			} else {
				buffer[p++] = infos[j++];
			}
		}
		for(int k = l; k < r; ++k) {
			infos[k] = buffer[k];
		}
	}
	vector<int> histogram() const {
		vector<int> ans(total_points, 0);
		for(const auto &info : infos) {
			ans[info.ans + info.cnt - 1] += info.cnt;
		}
		return ans;
	}
	void run_and_check() {
		run();
	}

private:
	static bool by_xyz(const ThreeDPartialOrderInfo &l,
					  const ThreeDPartialOrderInfo &r) {
		if(l.x != r.x) return l.x < r.x;
		if(l.y != r.y) return l.y < r.y;
		return l.z < r.z;
	}
	static bool by_yz(const ThreeDPartialOrderInfo &l,
					 const ThreeDPartialOrderInfo &r) {
		if(l.y != r.y) return l.y < r.y;
		return l.z < r.z;
	}
	static int compare_yz(const ThreeDPartialOrderInfo &l,
						  const ThreeDPartialOrderInfo &r) {
		if(l.y != r.y) return l.y < r.y ? -1 : 1;
		if(l.z != r.z) return l.z < r.z ? -1 : 1;
		return 0;
	}
	static bool same_point(const ThreeDPartialOrderInfo &l,
						   const ThreeDPartialOrderInfo &r) {
		return l.x == r.x && l.y == r.y && l.z == r.z;
	}
	int total_points;
	vector<ThreeDPartialOrderInfo> infos;
	vector<ThreeDPartialOrderInfo> buffer;
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
	REQUIRE(solver.histogram() == brute_histogram(pts));
}

TEST_CASE("cdq_single_point") {
	vector<ThreeDPartialOrderInfo> pts = {{1, 1, 1, 1, 0}};
	expect_histogram_matches_bruteforce(pts, 1);
}

TEST_CASE("cdq_all_duplicates") {
	vector<ThreeDPartialOrderInfo> pts = {
		{2, 2, 2, 1, 0}, {2, 2, 2, 1, 0}, {2, 2, 2, 1, 0}};
	expect_histogram_matches_bruteforce(pts, 2);
	REQUIRE(brute_histogram(pts) == vector<int>({0, 0, 3}));
}

TEST_CASE("cdq_mixed_small_case") {
	vector<ThreeDPartialOrderInfo> pts = {{1, 1, 1, 1, 0}, {1, 2, 1, 1, 0},
										  {2, 1, 2, 1, 0}, {2, 2, 2, 1, 0},
										  {2, 2, 2, 1, 0}, {3, 3, 1, 1, 0}};
	expect_histogram_matches_bruteforce(pts, 3);
}

TEST_CASE("cdq_randomized_against_bruteforce") {
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
