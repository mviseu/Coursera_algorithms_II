#include "DepthFirst.h"
#include <algorithm>

namespace {

void DepthFirstRec(std::vector<std::optional<int>>& comesFrom, int prev, const Graph& graph) {
	for(int adj : graph.Adj(prev)) {
		if(!comesFrom[adj]) {
			comesFrom[adj] = prev;
			DepthFirstRec(comesFrom, adj, graph);
		}
		// mark as visited?
	}
}

} // namespace

DepthFirst::DepthFirst(int source, const Graph& graph) : m_source(source), m_comesFrom(graph.V(), std::nullopt) {
	DepthFirstRec(m_comesFrom, source, graph);
}

bool DepthFirst::HasPath(int destination) const {
	if(destination == m_source) {
		return true;
	}
	return m_comesFrom[destination] != std::nullopt;
}

std::vector<int> DepthFirst::TracePath(int destination) const {
	if(destination == m_source) {
		return {m_source};
	}
	std::vector<int> path;
	path.push_back(destination);
	while(path.back() != m_source) {
		path.push_back(*m_comesFrom[path.back()]);
	}
	std::reverse(path.begin(), path.end());
	return path;
}