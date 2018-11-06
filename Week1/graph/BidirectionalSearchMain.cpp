#include "BidirectionalSearch.h"
#include "Graph.h"
#include <fstream>
#include <iterator>


namespace {

auto PrintPath(const std::optional<std::vector<int>>& path) -> void {
	if(path) {
		std::cout << "path is: " << std::endl;
		auto out = std::ostream_iterator<int>(std::cout, " ");
		std::copy(path->cbegin(), path->cend(), out);
		std::cout << std::endl;
	} else {
		std::cout << "no path was found" << std::endl;
	}
}


} // namespace

int main() {
	auto file = std::ifstream("BiSearchGraph.txt");
	auto gr = Graph(file);
	PrintPath(BidirectionalSearch(gr, 1, 11));
	PrintPath(BidirectionalSearch(gr, 11, 1));
	PrintPath(BidirectionalSearch(gr, 0, 8));
	PrintPath(BidirectionalSearch(gr, 8, 0));
	PrintPath(BidirectionalSearch(gr, 9, 8));
	PrintPath(BidirectionalSearch(gr, 10, 8));
	PrintPath(BidirectionalSearch(gr, 10, 9));
	PrintPath(BidirectionalSearch(gr, 10, 10));
	return 0;
}