#include "GraphCommon.h"
#include <algorithm>
#include <numeric>

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
