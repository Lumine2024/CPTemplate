#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

struct StrNum {
	StrNum() noexcept : number("0") {}
	StrNum(long long num) noexcept : number(to_string(num)) {}
	StrNum(const string &num) noexcept : number(num) {}
	StrNum(string &&num) noexcept : number(move(num)) {}
	StrNum operator+(const StrNum &r) const noexcept {
		return StrNum(move(add(number, r.number)));
	}
	StrNum &operator+=(const StrNum &r) noexcept {
		number = move(add(number, r.number));
		return *this;
	}
	StrNum operator-(const StrNum &r) const noexcept {
		return StrNum(move(minus(number, r.number)));
	}
	StrNum &operator-=(const StrNum &r) noexcept {
		number = move(minus(number, r.number));
		return *this;
	}
	StrNum operator*(const StrNum &r) const noexcept {
		return StrNum(move(mul(number, r.number)));
	}
	StrNum &operator*=(const StrNum &r) noexcept {
		number = move(mul(number, r.number));
		return *this;
	}
	StrNum operator-() const noexcept {
		if(number[0] == '-') return StrNum(number.substr(1, number.size() - 1));
		return StrNum('-' + number);
	}
	bool operator>(const StrNum &r) const noexcept {
		return gt(number, r.number);
	}
	bool operator<(const StrNum &r) const noexcept {
		return gt(r.number, number);
	}
	bool operator>=(const StrNum &r) const noexcept {
		return !gt(r.number, number);
	}
	bool operator<=(const StrNum &r) const noexcept {
		return !gt(number, r.number);
	}
	bool operator==(const StrNum &r) const noexcept {
		return number == r.number;
	}
	friend ostream &operator<<(ostream &os, const StrNum &r) noexcept {
		os << r.number;
		return os;
	}
	friend istream &operator>>(istream &is, StrNum &r) noexcept {
		is >> r.number;
		return is;
	}
private:
	string number;
	static bool gt(const string &a, const string &b) noexcept {
		if(a[0] == b[0] && a[0] == '-') {
			string suba = a.substr(1, a.size() - 1);
			string subb = b.substr(1, b.size() - 1);
			return (gt(subb, suba));
		}
		if(a[0] == '-') return false;
		if(b[0] == '-') return true;
		if(a.size() > b.size()) return true;
		if(a.size() < b.size()) return false;
		int n = a.size();
		for(int i = 0; i < n; i++) {
			if(a[i] > b[i]) return true;
			if(a[i] < b[i]) return false;
		}
		return false;
	}
	static string add(const string &a, const string &b) noexcept {
		if(a[0] == '-' && b[0] == '-') {
			string suba = a.substr(1, a.size() - 1);
			string subb = b.substr(1, b.size() - 1);
			return ("-" + add(suba, subb));
		}
		if(a[0] == '-') {
			string suba = a.substr(1, a.size() - 1);
			return minus(b, suba);
		}
		if(b[0] == '-') {
			string subb = b.substr(1, b.size() - 1);
			return minus(a, subb);
		}
		if(a.size() < b.size()) return add(b, a);
		string ans;
		string stra = a, strb = b;
		ranges::reverse(stra);
		ranges::reverse(strb);
		int s = stra.size();
		int carry = 0;
		for(int i = 0; i < s; i++) {
			if(i < strb.size()) {
				int m = (int)(stra[i] - '0'), n = (int)(strb[i] - '0');
				int p = m + n + carry;
				carry = 0;
				if(p < 10) ans.push_back((char)(p + '0'));
				else {
					ans.push_back((char)(p - 10 + '0'));
					carry = 1;
				}
			} else {
				int m = (int)(stra[i] - '0') + carry;
				carry = 0;
				if(m < 10) ans.push_back((char)(m + '0'));
				else {
					ans.push_back((char)('0'));
					carry = 1;
				}
			}
		}
		if(carry == 1) ans.push_back('1');
		ranges::reverse(ans);
		return ans;
	}
	static string mul(const string &a, const string &b) noexcept {
		if(a == "0" || b == "0") return "0";
		if(a == "1") return b;
		if(b == "1") return a;
		bool negative = (a[0] == '-') ^ (b[0] == '-');
		string stra = (a[0] == '-') ? a.substr(1) : a;
		string strb = (b[0] == '-') ? b.substr(1) : b;
		int n = stra.size();
		int m = strb.size();
		vector<int> result(n + m, 0);
		for(int i = n - 1; i >= 0; --i) {
			for(int j = m - 1; j >= 0; --j) {
				int mul = (stra[i] - '0') * (strb[j] - '0');
				int sum = mul + result[i + j + 1];
				result[i + j + 1] = sum % 10;
				result[i + j] += sum / 10;
			}
		}
		string ans;
		for(int num : result) {
			if(!(ans.empty() && num == 0)) {
				ans.push_back(num + '0');
			}
		}
		return negative ? '-' + ans : ans;
	}
	static string minus(const string &a, const string &b) noexcept {
		if(a == b) return "0";
		if(b[0] == '-') {
			string str = b.substr(1, b.size() - 1);
			return add(a, str);
		}
		if(a[0] == '-') {
			string str = a.substr(1, a.size() - 1);
			return '-' + add(str, b);
		}
		if(!gt(a, b)) {
			return '-' + minus(b, a);
		}
		string ans = "", stra = a, strb = b;
		ranges::reverse(stra);
		ranges::reverse(strb);
		int s = stra.size();
		int subtract = 0;
		for(int i = 0; i < s; i++) {
			if(i < strb.size()) {
				int k = stra[i] - strb[i] - subtract;
				subtract = 0;
				if(k < 0) {
					subtract = 1;
					k += 10;
				}
				ans.push_back((char)(k + '0'));
			} else {
				int k = stra[i] - subtract - '0';
				subtract = 0;
				if(k < 0) {
					subtract = 1;
					k += 10;
				}
				ans.push_back((char)(k + '0'));
			}
		}
		while(ans[ans.size() - 1] == '0') {
			ans.pop_back();
		}
		ranges::reverse(ans);
		return ans;
	}
};