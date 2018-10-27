#include "Trie.h"
#include <iostream>

int main() {
	Trie<int, 26> trie;
	std::cout << trie.Insert("Shell", 3) << std::endl;
	if(const auto findShe = trie.Find("She")) {
		std::cout << *findShe << std::endl;
	}
	return 0;
}