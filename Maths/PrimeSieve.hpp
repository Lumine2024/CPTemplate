#pragma once
#include <bits/stdc++.h>
#include "Maths/ModInt.hpp"
using namespace std;
using ll = long long;
using ull = unsigned long long;

ll 	phi[maxn], // 欧拉函数
	mu[maxn], // 莫比乌斯函数
	sigma0[maxn], // 因数个数
	sigma1[maxn], // 因数和
	lprime[maxn], // lowest prime，i==lprime[i]等价于i是质数
	lpower[maxn], // lprime[i]的次数
	powsum[maxn]; // \sum_{j=0}^{lpower[i]}(lprime[i])^j
vector<ll> primes;
int init = [] {
	primes.reserve(maxn / 10);
	phi[1] = mu[1] = sigma0[1] = sigma1[1] = powsum[1] = 1;
	lpower[1] = 0;
	for(ll i = 2; i < maxn; ++i) {
		if(lprime[i] == 0) {
			lprime[i] = i;
			primes.push_back(i);
			phi[i] = i - 1;
			mu[i] = -1;
			sigma0[i] = 2;
			lpower[i] = 1;
			powsum[i] = i + 1;
			sigma1[i] = powsum[i];
		}
		for(ll p : primes) {
			ll j = i * p;
			if(j >= maxn) break;
			lprime[j] = p;
			if(i % p == 0) {
				phi[j] = phi[i] * p;
				mu[j] = 0;
				lpower[j] = lpower[i] + 1;
				powsum[j] = powsum[i] + qpow(p, lpower[j]);
				sigma0[j] = sigma0[j / qpow(lprime[j], lpower[j])] * (lpower[j] + 1);
				sigma1[j] = sigma1[j / qpow(lprime[j], lpower[j])] * powsum[j];
				break;
			} else {
				phi[j] = phi[i] * (p - 1);
				mu[j] = -mu[i];
				lpower[j] = 1;
				powsum[j] = 1 + p;
				sigma1[j] = sigma1[i] * powsum[j];
				sigma0[j] = sigma0[i] * 2;
			}
		}
	}
	return 0;
}();