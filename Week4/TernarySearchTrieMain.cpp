#include "TernarySearchTrie.h"
#include <iostream>

int main() {
	TernarySearchTrie<int> tst;
	if(const auto findKey = tst.Find("somekey")) {
		std::cout << "found key" << std::endl;
	} else {
		std::cout << "did not find key" << std::endl;
	}
	return 0;
}