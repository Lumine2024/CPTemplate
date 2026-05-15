#include "binary/lis.h"
#include "../test.h"

TEST(lis_basic) {
	vector<int> a = {3, 1, 4, 1, 5, 9, 2, 6};
	auto result = lis(a);
	ENSURE(result.size() == 4); // LIS length is 4 (e.g., 1,4,5,9 or 1,4,5,6)
	// Verify it's non-decreasing and is a subsequence
	for(int i = 1; i < (int)result.size(); ++i) {
		ENSURE(result[i] > result[i - 1]);
	}
}

TEST(lis_already_sorted) {
	vector<int> a = {1, 2, 3, 4, 5};
	auto result = lis(a);
	ENSURE((int)result.size() == 5);
	ENSURE(result == a);
}

TEST(lis_reverse_sorted) {
	vector<int> a = {5, 4, 3, 2, 1};
	auto result = lis(a);
	ENSURE(result.size() == 1);
}

TEST(lis_single_element) {
	vector<int> a = {42};
	auto result = lis(a);
	ENSURE(result.size() == 1);
	ENSURE(result[0] == 42);
}

TEST(lis_all_same) {
	vector<int> a = {3, 3, 3, 3};
	auto result = lis(a);
	ENSURE(result.size() == 1);
}

TEST(lis_example) {
	vector<int> a = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};
	auto result = lis(a);
	ENSURE(result.size() == 6);
	for(int i = 1; i < (int)result.size(); ++i) {
		ENSURE(result[i] > result[i - 1]);
	}
}
