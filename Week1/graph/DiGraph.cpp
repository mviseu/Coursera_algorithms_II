#include "DiGraph.h"
#include "GraphCommon.h"
#include <ostringstream>


explicit DiGraph::operator std::string() const {
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