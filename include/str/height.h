#pragma once
#include "common.h"

vector<int> suffix_array(const string &str) {
	int n = str.size(), m = 128, p = 0;
	vector<int> rk(n * 3, -1), sa(n), id(n), cnt(max(n, m), 0);
	for(int i = 0; i < n; ++i) cnt[rk[i] = str[i]]++;
	for(int i = 1; i < m; ++i) cnt[i] += cnt[i - 1];
	for(int i = n - 1; i >= 0; --i) sa[--cnt[rk[i]]] = i;
	for(int w = 1;; w <<= 1, m = p + 1) {
		int cur = 0;
		for(int i = n - w; i < n; ++i) id[cur++] = i;
		for(int i = 0; i < n; ++i) {
			if(sa[i] >= w) id[cur++] = sa[i] - w;
		}
		cnt.assign(max(n, m), 0);
		for(int i = 0; i < n; ++i) cnt[rk[i]]++;
		for(int i = 1; i < m; ++i) cnt[i] += cnt[i - 1];
		for(int i = n - 1; i >= 0; --i) sa[--cnt[rk[id[i]]]] = id[i];
		p = 0;
		vector<int> oldrk = rk;
		rk[sa[0]] = 0;
		for(int i = 1; i < n; ++i) {
			if(oldrk[sa[i]] != oldrk[sa[i - 1]] ||
			   oldrk[sa[i] + w] != oldrk[sa[i - 1] + w])
				++p;
			rk[sa[i]] = p;
		}
		if(p == n - 1) break;
	}
	return sa;
}

vector<int> height(const string &str) {
	int n = str.size();
	vector<int> sa = suffix_array(str), rk(n), h(n);
	for(int i = 0; i < n; ++i) rk[sa[i]] = i;
	for(int i = 0, k = 0; i < n; ++i) {
		if(rk[i] == 0) continue;
		if(k > 0) --k;
		while(str[i + k] == str[sa[rk[i] - 1] + k]) ++k;
		h[rk[i]] = k;
	}
	return h;
}
