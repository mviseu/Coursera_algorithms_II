#include "Graph.h"
#include <algorithm>
#include <functional>
#include <numeric>
#include <stdexcept>
#include <sstream>

namespace {

std::vector<std::vector<int>> ReadEdges(std::istream& is, std::vector<std::vector<int>>&& adj, int nrEdges) {
	for(auto i = 0; i != nrEdges; ++i) {
		int first, second;
		if(is >> first && is >> second) {
			adj[first].push_back(second);
			adj[second].push_back(first);
		} else {
			throw std::runtime_error("Unable to read vertice in edge");
		}
	}
	return std::move(adj);
}

} // namespace

Graph::Graph(int v) : adjacents(std::vector<std::vector<int>>(v, std::vector<int>())) {}

Graph::Graph(std::istream& is) {
    int nrVertices = 0;
	if(is >> nrVertices) {
		adjacents = std::vector<std::vector<int>>(nrVertices, std::vector<int>());
		int nrEdges = 0;
		if(is >> nrEdges) {
			adjacents = ReadEdges(is, std::move(adjacents), nrEdges);
		}
	} else {
		throw std::runtime_error("Unable to read number of vertices or edges");
	}
} 
	
Graph::operator std::string() const {
	std::vector<std::vector<int>> adjacentsCopy;
	std::copy(adjacents.cbegin(), adjacents.cend(), std::back_inserter(adjacentsCopy));
	std::ostringstream os;
	os << V() << std::endl;
	os << E() << std::endl;
	for(auto adjacent = adjacentsCopy.cbegin(); adjacent != adjacentsCopy.cend(); ++adjacent) {
		const auto firstV = std::distance(adjacentsCopy.cbegin(), adjacent);
		for(int secondV : *adjacent) {
			os << firstV << " "  
			<< secondV << std::endl;
			auto pairedEdge = std::find(adjacentsCopy[secondV].begin(), adjacentsCopy[secondV].end(), firstV);
			adjacentsCopy[secondV].erase(pairedEdge);
		}
	}
	return os.str();
}

std::vector<int> Graph::Adj(int v) const {
	return adjacents[v];     
}

void Graph::AddEdge(int v, int w) {
	adjacents[v].push_back(w);
	adjacents[w].push_back(v);

}

int Graph::V() const {
	return adjacents.size();
}	

int Graph::E() const {
	const int pairedEdges = std::accumulate(adjacents.cbegin(), adjacents.cend(), 0, [](int lhs, const std::vector<int>& rhs) -> int {
			return lhs + static_cast<int>(rhs.size());
		});
	return pairedEdges / 2;
}
