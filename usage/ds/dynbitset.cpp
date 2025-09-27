
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;

template<class T, class F> concept binary_func = convertible_to<F, function<bool(T, T)>>;
template<class T1, class T2, class F> requires(binary_func<T1, F> &&convertible_to<T2, T1>) bool chkf(T1 &x, const T2 &y, F &&f) {
	if(f(static_cast<T1>(y), x)) {
		x = static_cast<T1>(y);
		return true;
	}
	return false;
}
template<class T1, class T2> bool chkmin(T1 &x, const T2 &y) {
	return chkf(x, y, less<T1>{});
}
template<class T1, class T2> bool chkmax(T1 &x, const T2 &y) {
	return chkf(x, y, greater<T1>{});
}

struct DynamicBitSet {
	explicit DynamicBitSet(int n = 0) : nums((n + 63) >> 6, 0), sz(n) {}
	void resize(int n) {
		nums.resize((n + 63) >> 6);
		sz = n;
	}
	bool getbit(int x) const {
		int u = x >> 6, v = x & 63;
		return ((nums[u] >> v) & 1) == 1;
	}
	void setbit(int x, bool val) {
		int u = x >> 6, v = x & 63;
		if(!val) {
			nums[u] &= (~(1ull << v));
		} else {
			nums[u] |= (1ull << v);
		}
	}
	void flipbit(int x) {
		setbit(x, !getbit(x));
	}
	DynamicBitSet &operator&=(const DynamicBitSet &other) {
		for(int i = 0; i < nums.size(); ++i) nums[i] &= other.nums[i];
		return *this;
	}
	DynamicBitSet operator&(const DynamicBitSet &other) const {
		DynamicBitSet ret = *this;
		ret &= other;
		return ret;
	}
	DynamicBitSet &operator|=(const DynamicBitSet &other) {
		for(int i = 0; i < nums.size(); ++i) nums[i] |= other.nums[i];
		return *this;
	}
	DynamicBitSet operator|(const DynamicBitSet &other) const {
		DynamicBitSet ret = *this;
		ret |= other;
		return ret;
	}
	DynamicBitSet &operator^=(const DynamicBitSet &other) {
		for(int i = 0; i < nums.size(); ++i) nums[i] ^= other.nums[i];
		return *this;
	}
	DynamicBitSet operator^(const DynamicBitSet &other) const {
		DynamicBitSet ret = *this;
		ret ^= other;
		return ret;
	}
	DynamicBitSet &operator<<=(int z) {
		int block = z >> 6, rem = z & 63, n = nums.size();
		if(rem == 0) {
			for(int i = n - 1; i >= block; --i) nums[i] = nums[i - block];
			fill(nums.begin(), nums.begin() + min(block, n), 0);
		} else {
			ull o1 = 0, o0 = 0;
			for(int i = n - block - 1; i >= 0; --i) {
				o0 = (nums[i] << rem);
				o1 |= (nums[i] >> (64 - rem));
				if(i + block + 1 < n) nums[i + block + 1] = o1;
				o1 = o0;
			}
			fill(nums.begin(), nums.begin() + min(block, n), 0);
			if(block < n) nums[block] = o0;
		}
		return *this;
	}
	DynamicBitSet operator<<(int z) const {
		DynamicBitSet ret = *this;
		ret <<= z;
		return ret;
	}
	DynamicBitSet &operator>>=(int z) {
		int block = z >> 6, rem = z & 63, n = nums.size();
		if(rem == 0) {
			for(int i = 0; i < n - block; ++i) nums[i] = nums[i + block];
			fill(nums.end() - min(n, block), nums.end(), 0);
		} else {
			ull o0 = 0, o1 = 0;
			for(int i = 0; i + block < n; ++i) {
				o1 |= (nums[i + block] << (64 - rem));
				o0 = (nums[i + block] >> rem);
				if(i != 0) nums[i - 1] = o1;
				o1 = o0;
			}
			fill(nums.end() - min(n, block + 1), nums.end(), 0);
			if(block <= n) nums[n - block - 1] = o0;
		}
		return *this;
	}
	DynamicBitSet operator>>(int z) const {
		DynamicBitSet ret = *this;
		ret >>= z;
		return ret;
	}
	bool allzero() const {
		int block = sz >> 6, rem = sz & 63;
		for(int i = 0; i < block; ++i) {
			if(nums[i] != 0ull) return false;
		}
		for(int i = block << 6; i < sz; ++i) {
			if(getbit(i)) return false;
		}
		return true;
	}
	int size() const { return sz; }
private:
	vector<ull> nums;
	int sz;
};

inline void solve() {
	
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
