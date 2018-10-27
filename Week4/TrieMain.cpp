#include "Trie.h"
#include <iostream>
#include <iterator>

constexpr const auto nrAlpha = 26;

void PrintVal(const Trie<int, nrAlpha>& trie, const std::string& key) {
	const auto val = trie.Find(key);
	if(val) {
		std::cout << "Value is " << *val 
				  << " for Key " << key << std::endl;
	} else {
		std::cout << "No Value found for Key " 
				  << key << std::endl;
	}

}

int main() {
	Trie<int, nrAlpha> trie;
	std::ostream_iterator<bool> out(std::cout, "\n");
	for(auto i = 0; i < 3; ++i) {
		out = trie.Insert("she", 0);
		out = trie.Insert("sells", 1);
		out = trie.Insert("sea", 2);
		out = trie.Insert("shells", 3);
		out = trie.Insert("by", 4);
		out = trie.Insert("the", 5);
		out = trie.Insert("sea", 6);
		out = trie.Insert("shore", 7);

		PrintVal(trie, "shells");
		PrintVal(trie, "she");
		PrintVal(trie, "sea");
		PrintVal(trie, "shel");
		PrintVal(trie, "shelter");
		PrintVal(trie, "random");
		PrintVal(trie, "shore");

		trie.Erase("sh");
		trie.Erase("she");
		trie.Erase("sells");
		trie.Erase("sea");
		trie.Erase("shells");
		trie.Erase("by");
		trie.Erase("the");
		trie.Erase("sea");
		trie.Erase("shore");
		trie.Erase("random");

		PrintVal(trie, "shells");
		PrintVal(trie, "she");
		PrintVal(trie, "sea");
		PrintVal(trie, "shel");
		PrintVal(trie, "shelter");
		PrintVal(trie, "random");
		PrintVal(trie, "shore");
	}

	return 0;
}