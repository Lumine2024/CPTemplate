#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

// 得到用于KMP的数组
vector<int> kmp_f(const string &str) {
	vector<int> f(str.size());
	int l = 0, r = 1;
	while(r < str.size()) {
		if(str[r] != str[l]) {
			if(l == 0) {
				f[r] = 0;
				++r;
			} else {
				l = f[l - 1];
			}
		} else {
			f[r] = l + 1;
			++r;
			++l;
		}
	}
	return f;
}
// 寻找第一次在off后面haystack中的needle
int kmp_find(const string &haystack, const string &needle, int off = 0) {
	int n = needle.size(), m = haystack.size();
	vector<int> f = kmp_f(needle);
	int i = 0, j = off;
	while(j < m) {
		if(haystack[j] == needle[i]) {
			++i;
			++j;
			if(i == n) {
				return j - n;
			}
		} else {
			if(i == 0) {
				++j;
			} else {
				i = f[i - 1];
			}
		}
	}
	return -1;
}
// 返回haystack中有多少个needle，可重（即10101有两个101）
int kmp_count(const string &haystack, const string &needle) {
	int n = needle.size(), m = haystack.size();
	int ret = 0;
	vector<int> f = kmp_f(needle);
	int i = 0, j = 0;
	while(j < m) {
		if(haystack[j] == needle[i]) {
			++i;
			++j;
			if(i == n) {
				++ret;
				i = f[i - 1];
			}
		} else {
			if(i == 0) {
				++j;
			} else {
				i = f[i - 1];
			}
		}
	}
	return ret;
}