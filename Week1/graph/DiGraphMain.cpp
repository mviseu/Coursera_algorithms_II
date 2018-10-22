#include "DiGraph.h"
#include "Cycles.h"
#include "DepthFirstOrder.h"
#include <algorithm>
#include <fstream>
#include <iterator>
#include <string>

int main() {
	/*
	std::ifstream file("TopologicalSortGraph.txt");
	DiGraph g(file);
	std::cout << std::string(g) << std::endl;
	const auto dfo = DepthFirstOrder(g);
	const auto topOrder = dfo.TopologicalSort();
	std::ostream_iterator<int> out(std::cout, " ");
	std::copy(topOrder.cbegin(), topOrder.cend(), out);
	std::cout << std::endl;
	*/

	std::cout << "Start of cycles" << std::endl;
	std::ifstream fileCycles("TinyDiGraph.txt");
	DiGraph g2(fileCycles);
	std::ostream_iterator<int> out(std::cout, " ");
	for(const auto& cycle : GetCycles(g2)) {
		std::copy(cycle.cbegin(), cycle.cend(), out);
		std::cout << std::endl;
	}
	return 0;
}