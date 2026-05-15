#pragma once
#include "common.h"

#ifndef LOCAL
#define debug(...) (void(0))
#else
string trim(string s) {
	size_t l = 0, r = s.size();
	while(l < r && isspace(s[l])) ++l;
	while(r > l && isspace(s[r - 1])) --r;
	return s.substr(l, r - l);
}
vector<string> split(string s) {
	vector<string> ret;
	size_t st = 0;
	int dep = 0;
	for(size_t i = 0; i < s.size(); ++i) {
		char ch = s[i];
		if(ch == '(' || ch == '[') ++dep;
		else if(ch == ')' || ch == ']') --dep;
		else if(dep == 0 && ch == ',') {
			auto tok = trim(s.substr(st, i - st));
			if(!tok.empty()) ret.push_back(tok);
			st = i + 1;
		}
	}
	auto tok = trim(s.substr(st));
	if(!tok.empty()) ret.push_back(tok);
	return ret;
}
template<class Tup, class F, size_t... I>
void tupf(Tup &&tp, F &&f, index_sequence<I...>) {
	(f(I, get<I>(tp)), ...);
}
template<class... Args>
void dbgh(string s, Args &&...args) {
	auto names = split(s);
	auto tp = forward_as_tuple(forward<Args>(args)...);
	bool first = true;
	tupf(
		tp,
		[&](int i, const auto &v) {
			if(!first) cerr << ", ";
			first = false;
			cerr << names[i] << " = " << v;
		},
		make_index_sequence<sizeof...(Args)>{});
	cerr << '\n';
}
#define debug(...) dbgh(#__VA_ARGS__, __VA_ARGS__)
#endif
