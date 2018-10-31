#include "Trie.h"
#include <iostream>
#include <iterator>

namespace {

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

void PrintWords(const std::vector<std::string>& words) {
	std::cout << "Starting to print all words" << std::endl;
	std::ostream_iterator<std::string> out(std::cout, "\n");
	std::copy(words.cbegin(), words.cend(), out);
}

} // namespace

int main() {
	Trie<int, nrAlpha> trie, trie2;
	std::ostream_iterator<bool> out(std::cout, "\n");
	for(auto i = 0; i < 1; ++i) {
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

		std::cout << "All keys" << std::endl;
		const auto keys = trie.Keys();
		PrintWords(keys);

		const auto pre = std::string("she");
		std::cout << "All keys with prefix " << pre << std::endl; 
		PrintWords(trie.KeysWithPrefix(pre));


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

		trie2.Insert("shelters", 2);
		trie2.Insert("she", 1);
		trie2.Insert("sh", 5);
		trie2.Insert("shelter", 4);
		const auto longestPrefix = trie2.LongestPrefixOf("shelters");
		std::cout << "Longest prefix of shelters is: " << longestPrefix << std::endl;
	}

	return 0;
}