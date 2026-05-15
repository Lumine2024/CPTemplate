// -------------------------------------------------------
// This file is generated using headers and tools from
// https://github.com/Lumine2024/CPTemplate
// License: MIT License
// -------------------------------------------------------

#pragma once
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;

template<class T1, class T2, class F>
bool chkf(T1 &x, const T2 &y, F &&f) {
	if(f(static_cast<T1>(y), x)) {
		x = static_cast<T1>(y);
		return true;
	}
	return false;
}
template<class T1, class T2>
bool chkmin(T1 &x, const T2 &y) {
	return chkf(x, y, less<T1>{});
}
template<class T1, class T2>
bool chkmax(T1 &x, const T2 &y) {
	return chkf(x, y, greater<T1>{});
}
