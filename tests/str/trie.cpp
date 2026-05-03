#include "str/trie.h"
#include "../test.h"

struct TrieCharTo62 {
	int operator()(char x) const {
		if(x >= 'A' && x <= 'Z') return x - 'A';
		if(x >= 'a' && x <= 'z') return x - 'a' + 26;
		return x - '0' + 52;
	}
};

TEST(trie_find_and_prefix_count) {
	Trie<62, TrieCharTo62> trie;
	trie.insert("Ab9");
	trie.insert("Abc");
	trie.insert("Ab9");

	ENSURE(trie.find("Ab9"));
	ENSURE(trie.find("Abc"));
	ENSURE(!trie.find("Ab"));
	ENSURE(!trie.find("Ac9"));
	ENSURE(trie.prefix_count("A") == 3);
	ENSURE(trie.prefix_count("Ab") == 3);
	ENSURE(trie.prefix_count("Ab9") == 2);
	ENSURE(trie.prefix_count("Abc") == 1);
	ENSURE(trie.prefix_count("Z") == 0);
}
