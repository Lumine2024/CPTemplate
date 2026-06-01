#include "str/trie.h"
#include "doctest.h"

struct TrieCharTo62 {
	int operator()(char x) const {
		if(x >= 'A' && x <= 'Z') return x - 'A';
		if(x >= 'a' && x <= 'z') return x - 'a' + 26;
		return x - '0' + 52;
	}
};

TEST_CASE("trie_find_and_prefix_count") {
	Trie<62, TrieCharTo62> trie;
	trie.insert("Ab9");
	trie.insert("Abc");
	trie.insert("Ab9");

	REQUIRE(trie.find("Ab9"));
	REQUIRE(trie.find("Abc"));
	REQUIRE(!trie.find("Ab"));
	REQUIRE(!trie.find("Ac9"));
	REQUIRE(trie.prefix_count("A") == 3);
	REQUIRE(trie.prefix_count("Ab") == 3);
	REQUIRE(trie.prefix_count("Ab9") == 2);
	REQUIRE(trie.prefix_count("Abc") == 1);
	REQUIRE(trie.prefix_count("Z") == 0);
}
