#include "ds/delheap.h"
#include "doctest.h"

TEST_CASE("delheap_empty") {
	DelHeap<int> heap;
	REQUIRE(heap.empty());
	REQUIRE(heap.size() == 0);
}

TEST_CASE("delheap_max_heap_and_lazy_deletion") {
	DelHeap<int> heap;
	for(int x : {4, 1, 7, 3}) heap.push(x);

	REQUIRE(heap.size() == 4);
	REQUIRE(heap.top() == 7);

	heap.pop(1);
	REQUIRE(heap.size() == 3);
	REQUIRE(heap.top() == 7);

	heap.pop(7);
	REQUIRE(heap.size() == 2);
	REQUIRE(heap.top() == 4);

	heap.push(9);
	REQUIRE(heap.size() == 3);
	REQUIRE(heap.top() == 9);
}

TEST_CASE("delheap_duplicate_values") {
	DelHeap<int> heap;
	heap.push(5);
	heap.push(2);
	heap.push(5);

	heap.pop(5);
	REQUIRE(heap.size() == 2);
	REQUIRE(heap.top() == 5);

	heap.pop(5);
	REQUIRE(heap.size() == 1);
	REQUIRE(heap.top() == 2);

	heap.pop(2);
	REQUIRE(heap.empty());
}

TEST_CASE("delheap_min_heap") {
	DelHeap<int, greater<int>> heap;
	for(int x : {4, 1, 7, 3}) heap.push(x);

	REQUIRE(heap.top() == 1);
	heap.pop(7);
	REQUIRE(heap.size() == 3);
	REQUIRE(heap.top() == 1);

	heap.pop(1);
	REQUIRE(heap.top() == 3);
	heap.pop(3);
	REQUIRE(heap.top() == 4);
}

TEST_CASE("delheap_interleaved_operations_match_multiset") {
	DelHeap<int> heap;
	multiset<int> expected;

	auto push = [&](int x) {
		heap.push(x);
		expected.insert(x);
	};
	auto erase = [&](int x) {
		auto it = expected.find(x);
		REQUIRE(it != expected.end());
		heap.pop(x);
		expected.erase(it);
	};
	auto check = [&] {
		REQUIRE(heap.size() == static_cast<int>(expected.size()));
		REQUIRE(heap.empty() == expected.empty());
		if(!expected.empty()) REQUIRE(heap.top() == *expected.rbegin());
	};

	for(int x : {3, 8, 1, 8, 5, 2}) push(x);
	check();

	erase(1);
	erase(8);
	check();

	push(6);
	erase(3);
	erase(8);
	check();

	erase(6);
	erase(2);
	erase(5);
	check();
}
