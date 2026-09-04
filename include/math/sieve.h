#pragma once
#include "common.h"

template<class F>
concept eularsieve_func = requires(F &&f, int p, int k, int pk) {
	// f(p, k, pk) returns f(p^k), where pk == p^k.
	{ f(p, k, pk) } -> convertible_to<ll>;
};

struct EularSieve {
	vector<int> primes, lpf, lpow, lpf_pow;
	vector<ll> fv;
	explicit EularSieve(int n) : lpf(n + 1), lpow(n + 1), lpf_pow(n + 1) {
		for(int i = 2; i <= n; ++i) {
			if(lpf[i] == 0) {
				lpf[i] = i;
				lpow[i] = 1;
				lpf_pow[i] = i;
				primes.push_back(i);
			}
			for(int p : primes) {
				ll product = 1ll * i * p;
				if(product > n) break;
				int j = static_cast<int>(product);
				lpf[j] = p;
				if(i % p == 0) {
					lpow[j] = lpow[i] + 1;
					lpf_pow[j] = lpf_pow[i] * p;
					break;
				} else {
					lpow[j] = 1;
					lpf_pow[j] = p;
				}
			}
		}
	}
	template<eularsieve_func F>
	EularSieve(int n, F &&f)
		: lpf(n + 1), lpow(n + 1), lpf_pow(n + 1), fv(n + 1) {
		if(n >= 1) fv[1] = 1;
		for(int i = 2; i <= n; ++i) {
			if(lpf[i] == 0) {
				lpf[i] = i;
				lpow[i] = 1;
				lpf_pow[i] = i;
				primes.push_back(i);
				fv[i] = f(i, 1, i);
			}
			for(int p : primes) {
				ll product = 1ll * i * p;
				if(product > n) break;
				int j = static_cast<int>(product);
				lpf[j] = p;
				if(i % p == 0) {
					lpow[j] = lpow[i] + 1;
					lpf_pow[j] = lpf_pow[i] * p;
					int rem = j / lpf_pow[j];
					fv[j] = fv[rem] * f(p, lpow[j], lpf_pow[j]);
					break;
				} else {
					fv[j] = fv[i] * fv[p];
					lpow[j] = 1;
					lpf_pow[j] = p;
				}
			}
		}
	}
};

constexpr ll eular_f(int p, int, int pk) {
	return pk - pk / p;
}
constexpr ll mobius_f(int, int k, int) {
	return k == 0 ? 1 : k == 1 ? -1 : 0;
}
constexpr ll factor_cnt_f(int, int k, int) {
	return k + 1;
}
constexpr ll factor_sum_f(int p, int, int pk) {
	return pk + (pk - 1ll) / (p - 1);
}
