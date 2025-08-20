
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;


template<class T, class F> bool chkf(T &x, const T &y, F &&f) {
    if(f(y, x)) {
        x = y;
        return true;
    }
    return false;
}
template<class T> bool chkmin(T &x, const T &y) {
    return chkf(x, y, less{});
}
template<class T> bool chkmax(T &x, const T &y) {
    return chkf(x, y, greater{});
}


#ifdef ONLINE_JUDGE
#define debug(...) (void(0))
#else

string trim(string s) {
    int l = 0, r = s.size() - 1;
    while(l <= r && isspace(s[l])) ++l;
    while(r >= l && isspace(s[r])) --r;
    return s.substr(l, r - l + 1);
}

vector<string> split_args(const string &s) {
    vector<string> ret;
    string cur;
    int dep = 0;
    for(char ch : s) {
        if(ch == '(' || ch == '[') {
            ++dep;
            cur += ch;
        } else if(ch == ')' || ch == ']') {
            --dep;
            cur += ch;
        } else if(dep == 0 && ch == ',') {
            ret.push_back(trim(cur));
            cur = "";
        } else {
            cur += ch;
        }
    }
    if(!(trim(cur).empty())) ret.push_back(trim(cur));
    return ret;
}

template<class Tuple, size_t ... I> void print_tuple(const vector<string> &names, const Tuple &t, index_sequence<I...>) {
    using expr = int[];
    bool first = true;
    (void)expr{0, ((void)(
        (first ? first = false : (bool)(cerr << ", ")),
        cerr << names[I] << " = " << get<I>(t)
    ), 0)...};
}

template<class ... Args> void debug_helper(const string &s, Args &&... args) {
    auto names = split_args(s);
    auto tp = forward_as_tuple(forward<Args>(args)...);
    print_tuple(names, tp, make_index_sequence<sizeof...(Args)>{});
    cerr << endl;
}

#define debug(...) debug_helper(#__VA_ARGS__, __VA_ARGS__)
#endif

inline void solve() {
    // Add your solution code here using the template above
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
