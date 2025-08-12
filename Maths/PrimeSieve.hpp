#pragma once
#include <bits/stdc++.h>
#include "Constants.hpp"
#include "ModInt.hpp"
using namespace std;
using ll = long long;
using ull = unsigned long long;

template<class F> concept eularsieve_func = convertible_to<F, function<int(int, int)>>;
template<class G> concept traverse_func = convertible_to<G, function<bool(int)>>;

struct EularSieve {
	template<eularsieve_func F> EularSieve(int n, F &&f) : lpf(n + 1), lpow(n + 1), fv(n + 1) {
		fv[1] = 1;
		for(ll i = 2; i <= n; ++i) {
			if(lpf[i] == 0) {
				lpf[i] = i;
				lpow[i] = 1;
				primes.push_back(i);
				fv[i] = f(i, 1);
			}
			for(ll p : primes) {
				ll j = i * p;
				if(j > n) break;
				lpf[j] = p;
				if(i % p == 0) {
					lpow[j] = lpow[i] + 1;
					ll jp = qpow(lpf[j], lpow[j]);
					ll rem = j / jp;
					if(rem == 1) {
						fv[j] = f(p, lpow[j]);
					} else {
						fv[j] = fv[rem] * fv[jp];
					}
					break;
				} else {
					fv[j] = fv[i] * fv[p];
					lpow[j] = 1;
				}
			}
		}
	}
	int lpf_of(int val) const { return lpf[val]; }
	int lpow_of(int val) const { return lpow[val]; }
	ll fv_of(int val) const { return fv[val]; }
	template<traverse_func G> void traverse_primes(G &&g) const {
		for(int i : primes) {
			if(!g(i)) break;
		}
	}
private:
	vector<int> lpf, lpow, primes;
	vector<ll> fv;
};

ll __qpow(ll x, ll n) {
	ll ret = 1;
	for(; n != 0; n >>= 1, x = x * x) {
		if(n & 1) ret = ret * x;
	}
	return ret;
}
int eular_f(int p, int k) {
	return __qpow(p, k) - __qpow(p, k - 1);
}
int mobius_f(int p, int k) {
	return k == 0 ? 1 : k == 1 ? -1 : 0;
}
int factor_cnt_f(int p, int k) {
	return k + 1;
}
int factor_sum_f(int p, int k) {
	return (__qpow(p, k + 1) - 1ll) / ll(p - 1);
}