#include "BreadthFirst.h"
#include "ConnectedComponents.h"
#include "DepthFirst.h"
#include "Graph.h"
#include "Paths.h"
#include <algorithm>
#include <fstream>
#include <iterator>
#include <memory>
#include <string>

void HasPathWrite(const Paths& paths, int dest) {
	std::cout << "dest " << dest
			  << " has path: " << paths.HasPath(dest)
			  << std::endl;
	if(paths.HasPath(dest)) {
		const auto trace = paths.TracePath(dest);
		std::ostream_iterator<int> os(std::cout, " ");
		std::copy(trace.cbegin(), trace.cend(), os);
		std::cout << std::endl;
	}
}

int main() {
	std::ifstream file("InputGraph.txt");
	Graph g(file);
	std::cout << std::string(g) << std::endl;
	std::unique_ptr<Paths> paths = std::make_unique<BreadthFirst>(BreadthFirst(0, g));
	HasPathWrite(*paths, 5);
	HasPathWrite(*paths, 8);
	HasPathWrite(*paths, 3);

	std::cout << "Get all connected components" << std::endl;
	const auto cc = ConnectedComponents(g);
	for(auto v = 0; v < g.V(); ++v) {
		if(cc.Id(v)) {
			std::cout << v << " is at connected component " << *cc.Id(v) << std::endl;
		} else {
			std::cout << v << " is not on any connected component" << std::endl;
		}
	}
	return 0;
}
