#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

struct HPINT {
	HPINT() : nums(1, 0), neg(false) {}
	HPINT(ll val) : neg(false) {
		if(val < 0) {
			neg = true;
			val = -val;
		}
		while(val) {
			int t = val % 10;
			nums.push_back(t);
			val /= 10;
		}
		if(nums.empty()) {
			nums = vector<int>(1, 0);
		}
	}
	HPINT &operator+=(const HPINT &r) {
		if(neg) {
			if(r.neg) {
				_add(nums, r.nums);
			} else {
				if(_cmp(nums, r.nums) == 1) {
					_sub(nums, r.nums);
				} else {
					vector<int> rnums = r.nums;
					_sub(rnums, nums);
					nums.swap(rnums);
					neg = false;
				}
			}
		} else {
			if(r.neg) {
				if(_cmp(nums, r.nums) != -1) {
					_sub(nums, r.nums);
				} else {
					vector<int> rnums = r.nums;
					_sub(rnums, nums);
					nums.swap(rnums);
					neg = true;
				}
			} else {
				_add(nums, r.nums);
			}
		}
		return *this;
	}
	HPINT &operator-=(const HPINT &r) {
		if(neg) {
			if(r.neg) {
				int c = _cmp(nums, r.nums);
				if(c == 1) {
					_sub(nums, r.nums);
				} else {
					vector<int> rnums = r.nums;
					_sub(rnums, nums);
					nums.swap(rnums);
					neg = false;
				}
			} else {
				_add(nums, r.nums);
			}
		} else {
			if(r.neg) {
				_add(nums, r.nums);
			} else {
				int c = _cmp(nums, r.nums);
				if(c == -1) {
					vector<int> rnums = r.nums;
					_sub(rnums, nums);
					nums.swap(rnums);
					neg = true;
				} else {
					_sub(nums, r.nums);
				}
			}
		}
		return *this;
	}
	HPINT &operator*=(const HPINT &r) {
		neg ^= r.neg;
		_mul(nums, r.nums);
		return *this;
	}
	friend ostream &operator<<(ostream &os, const HPINT &hp) {
		if(hp.neg) {
			os << '-';
		}
		for(int i = hp.nums.size() - 1; i >= 0; --i) {
			os << hp.nums[i];
		}
		return os;
	}
	friend istream &operator>>(istream &is, HPINT &hp) {
		char ch = is.rdbuf()->sbumpc();
		while(ch < '0' || ch > '9') {
			if(ch == '-') {
				hp.neg = true;
			}
			ch = is.rdbuf()->sbumpc();
		}
		string buffer;
		while(ch >= '0' && ch <= '9') {
			buffer += ch;
			ch = is.rdbuf()->sbumpc();
		}
		hp.nums.resize(buffer.size());
		int n = buffer.size();
		for(int i = 0; i < n; ++i) {
			hp.nums[i] = buffer[n - i - 1] - '0';
		}
		return is;
	}
	bool operator>(const HPINT &r) const {
		if(neg != r.neg) {
			return !neg && r.neg;
		}
		int c = _cmp(nums, r.nums);
		if(neg) {
			return c == -1;
		} else {
			return c == 1;
		}
	}
	bool operator<(const HPINT &r) const {
		return r > (*this);
	}
	bool operator==(const HPINT &r) const {
		return neg == r.neg && _cmp(nums, r.nums) == 0;
	}
	HPINT operator+(const HPINT &r) const {
		HPINT ret = *this;
		ret += r;
		return ret;
	}
	HPINT operator-(const HPINT &r) const {
		HPINT ret = *this;
		ret -= r;
		return ret;
	}
	HPINT operator*(const HPINT &r) const {
		HPINT ret = *this;
		ret *= r;
		return ret;
	}
	bool operator>=(const HPINT &r) const {
		return !operator<(r);
	}
	bool operator<=(const HPINT &r) const {
		return !operator>(r);
	}
private:
	vector<int> nums;
	bool neg;
	static void _add(vector<int> &a, const vector<int> &b) {
		int carry = 0;
		for(int i = 0; i < b.size(); ++i) {
			if(i >= a.size()) {
				a.push_back(0);
			}
			a[i] += (b[i] + carry);
			carry = 0;
			if(a[i] >= 10) {
				carry = 1;
				a[i] -= 10;
			}
		}
		int i = b.size();
		while(carry != 0) {
			if(i >= a.size()) {
				a.push_back(0);
			}
			a[i] += carry;
			carry = 0;
			if(a[i] >= 10) {
				carry = 1;
				a[i] -= 10;
			}
		}
	}
	static void _sub(vector<int> &a, const vector<int> &b) {
		int borrow = 0;
		for(int i = 0; i < b.size(); ++i) {
			a[i] -= (borrow + b[i]);
			borrow = 0;
			if(a[i] < 0) {
				a[i] += 10;
				borrow = 1;
			}
		}
		int i = b.size();
		while(borrow && i < a.size()) {
			a[i] -= borrow;
			borrow = 0;
			if(a[i] < 0) {
				a[i] += 10;
				borrow = 1;
			}
			i++;
		}
		while(a.size() > 1 && a.back() == 0) {
			a.pop_back();
		}
	}
	static void _mul(vector<int> &a, const vector<int> &b) {
		using cd = complex<double>;
		constexpr double pi = 3.14159265358979323846264338327950288;
		int n = 1;
		while(n < (int)(a.size() + b.size())) {
			n <<= 1;
		}
		vector<cd> fa(n), fb(n);
		for(int i = 0; i < (int)a.size(); ++i) {
			fa[i] = a[i];
		}
		for(int i = 0; i < (int)b.size(); ++i) {
			fb[i] = b[i];
		}
		auto fft = [](auto &&fft, vector<cd> &f, bool invert) -> void {
			int n = f.size();
			if(n == 1)
				return;
			vector<cd> f0(n / 2), f1(n / 2);
			for(int i = 0; i < n / 2; ++i) {
				f0[i] = f[2 * i];
				f1[i] = f[2 * i + 1];
			}
			fft(fft, f0, invert);
			fft(fft, f1, invert);
			double theta = 2 * pi / n * (invert ? -1 : 1);
			cd wt = 1, w(cos(theta), sin(theta));
			for(int t = 0; t < n / 2; ++t) {
				cd u = f0[t], v = wt * f1[t];
				f[t] = u + v;
				f[t + n / 2] = u - v;
				wt *= w;
			}
		};
		fft(fft, fa, false);
		fft(fft, fb, false);
		for(int i = 0; i < n; ++i) {
			fa[i] *= fb[i];
		}
		fft(fft, fa, true);
		a.resize(n);
		int carry = 0;
		for(int i = 0; i < n; ++i) {
			int num = int(fa[i].real() / n + 0.5) + carry;
			carry = num / 10;
			a[i] = num % 10;
		}
		while(carry) {
			a.push_back(carry % 10);
			carry /= 10;
		}
		while(a.size() > 1 && a.back() == 0) {
			a.pop_back();
		}
	}
	// 1 gt, -1 lt, 0 eq
	static int _cmp(const vector<int> &a, const vector<int> &b) {
		if(a.size() > b.size())
			return 1;
		if(a.size() < b.size())
			return -1;
		for(int n = a.size(), i = n - 1; i >= 0; --i) {
			if(a[i] > b[i])
				return 1;
			if(a[i] < b[i])
				return -1;
		}
		return 0;
	}
};