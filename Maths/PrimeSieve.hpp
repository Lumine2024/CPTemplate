#pragma once
#include <bits/stdc++.h>
#include "Constants.hpp"
#include "ModInt.hpp"
using namespace std;
using ll = long long;
using ull = unsigned long long;

// 为了筛更多的数，需要尽量减少数组的数量，牺牲一点时间
int lpf[maxn];
int myf[maxn];
vector<int> primes;

// 示例：欧拉函数（积性函数）
int getf(int p, int k) {
	return qpow(p, k) - qpow(p, k - 1);
}

int init_myf = [] {
	myf[1] = 1; // 积性函数首项为1
	for(int i = 2; i < maxn; ++i) {
		if(lpf[i] == 0) {
			lpf[i] = i;
			primes.push_back(i);
			myf[i] = getf(i, 1);
		}
		for(ll p : primes) {
			if(i * p >= maxn) break;
			int j = i * p;
			lpf[j] = p;
			if(i % p == 0) {
				int k = 0, t = j;
				while(t % p == 0) {
					++k;
					t /= p;
				}
				if(t == 1) {
					myf[j] = getf(p, k);
				} else {
					myf[j] = myf[t] * myf[j / t];
				}
				break;
			} else {
				myf[j] = myf[i] * myf[p];
			}
		}
	}
	return 0;
}();