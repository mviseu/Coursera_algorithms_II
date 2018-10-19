#include "GraphCommon.h"
#include <algorithm>
#include <numeric>

auto ReadNrVertices(std::istream& is) -> int {
	int nrVertices;
	if(!(is >> nrVertices)) {
		throw std::runtime_error("Unable to read number of vertices");
	}
	return nrVertices;
}

auto ReadNrEdges(std::istream& is) -> int {
	int nrEdges = 0;
	if(!(is >> nrEdges)) {
		throw std::runtime_error("Unable to read nr of edges");	
	}
	return nrEdges;
}

auto ReadOutEdges(std::istream& is, int nrEdges) -> std::vector<std::pair<int, int>> {
	std::vector<std::pair<int, int>> edges;
	for(auto i = 0; i != nrEdges; ++i) {
		int first, second;
		if(is >> first && is >> second) {
			edges.emplace_back(std::make_pair(first, second));
		} else {
			throw std::runtime_error("Unable to read vertice in edge");
		}
	}
	return edges;
}

auto CreateEmptyGraph(int v) -> std::vector<std::vector<int>> {
	return std::vector<std::vector<int>>(v, std::vector<int>());
}

auto PrintEdges(std::ostream& os, const std::vector<std::vector<int>>& outEdges) -> std::ostream& {
	for(auto v = 0; v < CountVertices(outEdges); ++v) {
		for(auto e = 0; e < static_cast<int>(outEdges[v].size()); ++e) {
			os << v << " " << outEdges[v][e] << std::endl;
		}	
	}
	return os;
}

auto AddOutEdge(std::vector<std::vector<int>>& outEdges, int from, int to) -> void {
	outEdges[from].push_back(to);
}

auto GetOutEdges(const std::vector<std::vector<int>>& outEdges, int v) -> std::vector<int> {
	return outEdges[v];
}

auto CountVertices(const std::vector<std::vector<int>>& outEdges) -> int {
	return outEdges.size();
}


auto CountEdges(const std::vector<std::vector<int>>& outEdges) -> int {
	return std::accumulate(outEdges.cbegin(), outEdges.cend(), 0, [](int lhs, const std::vector<int>& rhs) -> int {
			return lhs + static_cast<int>(rhs.size());
		});
}
