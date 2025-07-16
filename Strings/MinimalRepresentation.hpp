#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

string minstr(const string &str) {
	int n = str.size(), i = 0, j = 1, k = 0;
	string s = str + str;
	while(i < n && j < n) {
		while(k < n && s[i + k] == s[j + k]) {
			++k;
		}
		if(k == n)
			break;
		if(s[i + k] > s[j + k]) {
			i += (k + 1);
		} else {
			j += (k + 1);
		}
		if(i == j) {
			++j;
		}
		k = 0;
	}
	return s.substr(min(i, j), n);
}