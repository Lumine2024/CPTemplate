#include "geo/fp/ccinter.h"
#include "doctest.h"

static vector<ld> arc_spans(const vector<Arc> &arcs, int n) {
	vector<ld> ret(n);
	for(const auto &[idx, alpha, beta] : arcs) ret[idx] += beta - alpha;
	return ret;
}

static void check_arc_points(const vector<Circle> &circs,
							 const vector<Arc> &arcs) {
	for(const auto &[idx, alpha, beta] : arcs) {
		REQUIRE(idx >= 0);
		REQUIRE(idx < (int)circs.size());
		REQUIRE(cmp(alpha, 0.0l) != -1);
		REQUIRE(cmp(alpha, 2 * pi) == -1);
		REQUIRE(cmp(alpha, beta) == -1);
		REQUIRE(cmp(beta - alpha, 2 * pi) != 1);
		ld mid = (alpha + beta) / 2;
		Point p = circs[idx].c + Point(circs[idx].r, 0.0l).rotate(mid);
		for(const auto &c : circs) CHECK(is_in(p, c));
	}
}

TEST_CASE("circle_inter_empty_and_single_circle") {
	CHECK(circle_inter({}).empty());
	for(ld r : {0.0l, 2.0l}) {
		vector<Circle> circs = {Circle(Point(1.0l, -3.0l), r)};
		auto arcs = circle_inter(circs);
		REQUIRE(arcs.size() == 1);
		CHECK(arcs[0].idx == 0);
		CHECK(cmp(arcs[0].alpha, 0.0l) == 0);
		CHECK(cmp(arcs[0].beta, 2 * pi) == 0);
		check_arc_points(circs, arcs);
	}
}

TEST_CASE("circle_inter_two_overlapping_circles") {
	vector<Circle> circs = {
		Circle(Point(0.0l, 0.0l), 1.0l),
		Circle(Point(1.0l, 0.0l), 1.0l),
	};
	auto arcs = circle_inter(circs);
	auto spans = arc_spans(arcs, 2);
	REQUIRE(arcs.size() == 2);
	CHECK(cmp(spans[0], 2 * pi / 3) == 0);
	CHECK(cmp(spans[1], 2 * pi / 3) == 0);
	CHECK(cmp(arcs[0].alpha, 5 * pi / 3) == 0);
	CHECK(cmp(arcs[0].beta, 7 * pi / 3) == 0);
	CHECK(cmp(arcs[1].alpha, 2 * pi / 3) == 0);
	CHECK(cmp(arcs[1].beta, 4 * pi / 3) == 0);
	check_arc_points(circs, arcs);
}

TEST_CASE("circle_inter_containment_and_coincident_circles") {
	SUBCASE("strict containment") {
		vector<Circle> circs = {
			Circle(Point(0.0l, 0.0l), 3.0l),
			Circle(Point(0.5l, 0.0l), 1.0l),
		};
		auto arcs = circle_inter(circs);
		REQUIRE(arcs.size() == 1);
		CHECK(arcs[0].idx == 1);
		CHECK(cmp(arcs[0].beta - arcs[0].alpha, 2 * pi) == 0);
		check_arc_points(circs, arcs);
	}
	SUBCASE("coincident circles") {
		vector<Circle> circs(2, Circle(Point(2.0l, -1.0l), 3.0l));
		auto arcs = circle_inter(circs);
		auto spans = arc_spans(arcs, 2);
		REQUIRE(arcs.size() == 2);
		CHECK(cmp(spans[0], 2 * pi) == 0);
		CHECK(cmp(spans[1], 2 * pi) == 0);
		check_arc_points(circs, arcs);
	}
}

TEST_CASE("circle_inter_disjoint_and_tangent_circles") {
	SUBCASE("disjoint") {
		vector<Circle> circs = {
			Circle(Point(0.0l, 0.0l), 1.0l),
			Circle(Point(3.0l, 0.0l), 1.0l),
		};
		CHECK(circle_inter(circs).empty());
	}
	SUBCASE("external tangency has no positive-length arc") {
		vector<Circle> circs = {
			Circle(Point(0.0l, 0.0l), 1.0l),
			Circle(Point(2.0l, 0.0l), 1.0l),
		};
		CHECK(circle_inter(circs).empty());
	}
	SUBCASE("internal tangency keeps the smaller circle") {
		vector<Circle> circs = {
			Circle(Point(0.0l, 0.0l), 2.0l),
			Circle(Point(1.0l, 0.0l), 1.0l),
		};
		auto arcs = circle_inter(circs);
		REQUIRE(arcs.size() == 1);
		CHECK(arcs[0].idx == 1);
		CHECK(cmp(arcs[0].beta - arcs[0].alpha, 2 * pi) == 0);
		check_arc_points(circs, arcs);
	}
}

TEST_CASE("circle_inter_zero_radius") {
	SUBCASE("point circle inside") {
		vector<Circle> circs = {
			Circle(Point(0.0l, 0.0l), 2.0l),
			Circle(Point(0.5l, 0.0l), 0.0l),
		};
		auto arcs = circle_inter(circs);
		REQUIRE(arcs.size() == 1);
		CHECK(arcs[0].idx == 1);
		CHECK(cmp(arcs[0].beta - arcs[0].alpha, 2 * pi) == 0);
		check_arc_points(circs, arcs);
	}
	SUBCASE("point circle on the boundary") {
		vector<Circle> circs = {
			Circle(Point(0.0l, 0.0l), 2.0l),
			Circle(Point(2.0l, 0.0l), 0.0l),
		};
		auto arcs = circle_inter(circs);
		REQUIRE(arcs.size() == 1);
		CHECK(arcs[0].idx == 1);
		CHECK(cmp(arcs[0].beta - arcs[0].alpha, 2 * pi) == 0);
		check_arc_points(circs, arcs);
	}
	SUBCASE("point circle outside") {
		vector<Circle> circs = {
			Circle(Point(0.0l, 0.0l), 1.0l),
			Circle(Point(2.0l, 0.0l), 0.0l),
		};
		CHECK(circle_inter(circs).empty());
	}
}

TEST_CASE("circle_inter_can_return_two_arcs_for_one_circle") {
	ld r = sqrt(105.0l);
	vector<Circle> circs = {
		Circle(Point(0.0l, 0.0l), 1.0l),
		Circle(Point(0.0l, 10.0l), r),
		Circle(Point(0.0l, -10.0l), r),
	};
	auto arcs = circle_inter(circs);
	auto spans = arc_spans(arcs, 3);
	CHECK(count_if(arcs.begin(), arcs.end(),
				   [](const Arc &arc) { return arc.idx == 0; }) == 2);
	CHECK(cmp(spans[0], 4 * asin(0.2l)) == 0);
	check_arc_points(circs, arcs);
}
