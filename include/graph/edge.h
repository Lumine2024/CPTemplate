#pragma once
#include "common.h"

template<class Edge>
concept WeightedEdgeT = requires(Edge edge) {
	{ edge.v } -> convertible_to<int>;
	{ edge.w } -> convertible_to<ll>;
};

struct WeightedEdge {
	int v;
	ll w;
};

static_assert(WeightedEdgeT<WeightedEdge>);

inline constexpr ll inf = 0x3f3f3f3f3f3f3f3f;
