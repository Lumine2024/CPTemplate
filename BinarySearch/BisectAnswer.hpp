#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

template<class T> T binary(auto &&check, T minv, T maxv, T eps, T delta) {
	T ans{};
	while((maxv - minv) > eps) {
		T mid = (minv + maxv) / 2;
		if(check(mid)) {
			ans = mid;
			hi = mid - delta;
		} else {
			lo = mid + delta;
		}
	}
	return ans;
}