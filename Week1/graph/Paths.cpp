#include "Paths.h"
#include <algorithm>
#include <optional>

namespace {

void DepthFirst(std::vector<std::optional<int>>& comesFrom, int prev, const Graph& graph) {
	for(int adj : graph.Adj(prev)) {
		if(!comesFrom[adj]) {
			comesFrom[adj] = prev;
			DepthFirst(comesFrom, adj, graph);
		}
		// mark as visited?
	}
}

} // namespace

bool Paths::HasPath(int destination) const {
	return m_comesFrom[destination] != std::nullopt;
}

std::vector<int> Paths::TracePath(int destination) const {
	std::vector<int> path;
	path.push_back(destination);
	while(path.back() != m_source) {
		path.push_back(*m_comesFrom[path.back()]);
	}
	std::reverse(path.begin(), path.end());
	return path;
}

Paths::Paths(int source, const Graph& graph) : m_source(source), m_comesFrom(graph.V(), std::nullopt) {
	DepthFirst(m_comesFrom, source, graph);
}
