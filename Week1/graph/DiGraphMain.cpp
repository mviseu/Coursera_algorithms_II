#include "DiGraph.h"
#include "DepthFirstOrder.h"
#include <algorithm>
#include <fstream>
#include <iterator>
#include <string>

int main() {
	std::ifstream file("TopologicalSortGraph.txt");
	DiGraph g(file);
	std::cout << std::string(g) << std::endl;
	const auto dfo = DepthFirstOrder(g);
	const auto topOrder = dfo.TopologicalSort();
	std::ostream_iterator<int> out(std::cout, " ");
	std::copy(topOrder.cbegin(), topOrder.cend(), out);
	return 0;
}