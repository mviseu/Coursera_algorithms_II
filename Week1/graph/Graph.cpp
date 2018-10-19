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


std::vector<std::vector<int>> GetEdges(std::vector<std::vector<int>>&& adj, const std::vector<std::pair<int, int>>& outEdges) {
	for(const auto& outEdge : outEdges) {
		adj[outEdge.first].push_back(outEdge.second);
		adj[outEdge.second].push_back(outEdge.first);
	}
	return std::move(adj);
}

} // namespace

Graph::Graph(int v) : adjacents(CreateEmptyGraph(v)) {}

Graph::Graph(std::istream& is) {
    int nrVertices = ReadNrVertices(is);
    adjacents = CreateEmptyGraph(nrVertices);
    int nrEdges = ReadNrEdges(is);
	adjacents = GetEdges(std::move(adjacents), ReadOutEdges(is, nrEdges));
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
