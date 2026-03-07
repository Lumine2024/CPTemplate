#pragma once
#include <bits/stdc++.h>

std::vector<std::pair<std::string, std::function<void(int &)>>> actions;

int main() {
	int fail_cnt = 0;
	int total_cnt = actions.size();
	std::vector<std::string> failed_tests;
	for(auto [name, action] : actions) {
		std::cout << "Running test " << name << '\n';
		int ec = 0;
		action(ec);
		if(ec == 0) std::cout << "OK\n";
		else {
			std::cout << "Failed\n";
			fail_cnt++;
			failed_tests.push_back(name);
		}
	}
	std::cout << "Passed: " << (total_cnt - fail_cnt) << " / " << total_cnt
			  << " tests\n";
	if(fail_cnt != 0) {
		std::cout << "Following tests failed:\n";
		for(auto &ft : failed_tests) {
			std::cout << ft << '\n';
		}
	}
	return fail_cnt == 0 ? 0 : 1;
}

#define TEST(test_name)                                                        \
	void test_name(int &ec);                                                   \
	int __init_##test_name##__ = [] {                                          \
		actions.emplace_back(#test_name, test_name);                           \
		return 0;                                                              \
	}();                                                                       \
	void test_name(int &ec)

#define ENSURE(cond)                                                           \
	do {                                                                       \
		if(!(cond)) {                                                          \
			ec = 1;                                                            \
			return;                                                            \
		}                                                                      \
	} while(false);
