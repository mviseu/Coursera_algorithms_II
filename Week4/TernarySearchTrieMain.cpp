#include "TernarySearchTrie.h"
#include <iostream>
#include <iterator>

namespace {

void PrintVal(const TernarySearchTrie<int>& tst, const std::string& key) {
	const auto val = tst.Find(key);
	if(val) {
		std::cout << "Value is " << *val 
				  << " for Key " << key << std::endl;
	} else {
		std::cout << "No Value found for Key " 
				  << key << std::endl;
	}
}

} // namespace


int main() {
	TernarySearchTrie<int> tst;
	std::ostream_iterator<bool> out(std::cout, "\n");
	for(auto i = 0; i < 3; ++i) {
		out = tst.Insert("she", 0);
		out = tst.Insert("sells", 1);
		out = tst.Insert("sea", 2);
		out = tst.Insert("shells", 3);
		out = tst.Insert("by", 4);
		out = tst.Insert("the", 5);
		out = tst.Insert("sea", 6);
		out = tst.Insert("shore", 7);

		PrintVal(tst, "shells");
		PrintVal(tst, "she");
		PrintVal(tst, "sea");
		PrintVal(tst, "shel");
		PrintVal(tst, "shelter");
		PrintVal(tst, "random");
		PrintVal(tst, "shore");

		tst.Erase("sh");
		tst.Erase("she");
		tst.Erase("sells");
		tst.Erase("sea");
		tst.Erase("shells");
		tst.Erase("by");
		tst.Erase("the");
		tst.Erase("sea");
		tst.Erase("shore");
		tst.Erase("random");

		PrintVal(tst, "shells");
		PrintVal(tst, "she");
		PrintVal(tst, "sea");
		PrintVal(tst, "shel");
		PrintVal(tst, "shelter");
		PrintVal(tst, "random");
		PrintVal(tst, "shore");
	}
	return 0;
}