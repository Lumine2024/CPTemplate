#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

vector<string> duval(const string &s) {
    int n = s.size();
    vector<string> ret;
    for(int i = 0; i < n;) {
        int j = i + 1, k = i;
        while(j < n && s[k] <= s[j]) {
            (s[k] < s[j]) ? (k = i) : (k++);
            ++j;
        }
        while(i <= k) {
            ret.push_back(s.substr(i, j - k));
            i += (j - k);
        }
    }
    return ret;
}