#include "ds/trie01.h"
#include "../test.h"

TEST(trie01_basic_xor) {
	Trie01 t;
	t.insert(5);  // 101
	t.insert(3);  // 011
	// 5 XOR 3 = 6, 5 XOR 5 = 0, 3 XOR 3 = 0
	ENSURE(t.qmax_xor(5) == 6);  // 5^3 = 6
	ENSURE(t.qmax_xor(3) == 6);  // 3^5 = 6
}

TEST(trie01_max_xor_single) {
	Trie01 t;
	t.insert(0);
	ENSURE(t.qmax_xor(0) == 0);
	t.insert(7);  // 111
	ENSURE(t.qmax_xor(0) == 7);
	ENSURE(t.qmax_xor(7) == 7);  // 7^0=7
}

TEST(trie01_large_values) {
	Trie01 t;
	ll a = (1LL << 60) - 1;  // all 60 lower bits set
	ll b = 0;
	t.insert(a);
	t.insert(b);
	ENSURE(t.qmax_xor(0) == a);
	ENSURE(t.qmax_xor(a) == a);  // a ^ 0 = a
}

TEST(trie01_multiple_values) {
	Trie01 t;
	for(ll i = 0; i < 8; ++i) t.insert(i);
	// XOR with 0: best is 7 (0^7 = 7)
	ENSURE(t.qmax_xor(0) == 7);
	// XOR with 7: best is 0 (7^0 = 7) or something similar
	ENSURE(t.qmax_xor(7) == 7);
}
