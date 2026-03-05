#include "../common.h"

struct Qread {
	Qread() : state(true) {
		cin.rdbuf()->pubsetbuf(buffer, maxn);
	}
	template<integral T> Qread &operator>>(T &val) {
		if(!state) {
			val = 0;
			return *this;
		}
		T x = 0, f = 1;
		char ch = cin.rdbuf()->sbumpc();
		while(ch < '0' || ch > '9') {
			if(ch == char_traits<char>::eof()) {
				state = false;
				cin.setstate(ios_base::eofbit);
				val = x * f;
				return *this;
			}
			if(ch == '-') {
				f = -1;
			}
			ch = cin.rdbuf()->sbumpc();
		}
		while(ch >= '0' && ch <= '9') {
			x = x * 10 + ch - '0';
			ch = cin.rdbuf()->sbumpc();
		}
		val = x * f;
		return *this;
	}
	explicit operator bool() const {
		return state;
	}

private:
	bool state;
	static constexpr int maxn = 1 << 21;
	char buffer[maxn];
} qread;

inline void solve() {}

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
