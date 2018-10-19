#include "Graph.h"
#include "GraphCommon.h"
#include <algorithm>
#include <functional>
#include <numeric>
#include <stdexcept>
#include <sstream>

namespace {

std::vector<std::vector<int>> RemoveDuplicates(const std::vector<std::vector<int>>& adjacents) {
	std::vector<std::vector<int>> cpAdj;
	std::copy(adjacents.cbegin(), adjacents.cend(), std::back_inserter(cpAdj));
	for(auto v = 0; v < CountVertices(cpAdj); ++v) {
		for(auto eIndex = 0; eIndex < static_cast<int>(cpAdj[v].size()); ++eIndex) {
			const auto e = cpAdj[v][eIndex];
			auto vInE = std::find(cpAdj[e].begin(), cpAdj[e].end(), v);
			cpAdj[e].erase(vInE);
		}
	}
	return cpAdj;
}


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
	std::ostringstream os;
	os << V() << std::endl;
	os << E() << std::endl;
	PrintEdges(os, RemoveDuplicates(adjacents));
	return os.str();
}

std::vector<int> Graph::Adj(int v) const {
	return GetOutEdges(adjacents, v);
}


void Graph::AddEdge(int v, int w) {
	AddOutEdge(adjacents, v, w);
	AddOutEdge(adjacents, w, v);
}

int Graph::V() const {
	return CountVertices(adjacents);
}	

int Graph::E() const {
	return CountEdges(adjacents) / 2;
}
