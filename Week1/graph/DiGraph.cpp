#include "DiGraph.h"
#include "GraphCommon.h"
#include <algorithm>
#include <sstream>

namespace {

auto GetEdges(std::vector<std::vector<int>>&& adj, const std::vector<std::pair<int, int>>& outEdges) -> std::vector<std::vector<int>> {
	for(const auto& outEdge : outEdges) {
		adj[outEdge.first].push_back(outEdge.second);
	}
	return std::move(adj);
}

} // namespace


DiGraph::DiGraph(std::istream& is) {
    int nrVertices = ReadNrVertices(is);
    m_outEdges = CreateEmptyGraph(nrVertices);
    int nrEdges = ReadNrEdges(is);
	m_outEdges = GetEdges(std::move(m_outEdges), ReadOutEdges(is, nrEdges));
} 

DiGraph::DiGraph(int v) : m_outEdges(CreateEmptyGraph(v)) {}

DiGraph::operator std::string() const {
	std::ostringstream os;
	os << V() << std::endl;
	os << E() << std::endl;
	PrintEdges(os, m_outEdges);
	return os.str();
}

auto DiGraph::AddEdge(int v, int w) -> void {
	AddOutEdge(m_outEdges, v, w);
}

auto DiGraph::Adj(int v) const -> std::vector<int> {
	return GetOutEdges(m_outEdges, v);
}

auto DiGraph::V() const -> int {
	return CountVertices(m_outEdges);
}

auto DiGraph::E() const -> int {
	return CountEdges(m_outEdges);
}