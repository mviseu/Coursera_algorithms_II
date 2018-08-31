#include "BreadthFirst.h"
#include <algorithm>
#include <queue>

BreadthFirst::BreadthFirst(int source, const Graph& graph) : m_source(source), m_comesFrom(graph.V(), std::nullopt) {
	std::queue<int> q;
	// ensure source is marked
	const auto sAdjs = graph.Adj(source);
	if(!sAdjs.empty()) {
		m_comesFrom[source] = sAdjs.front();
		q.push(source);
	}
	while(!q.empty()) {
		for(auto adj : graph.Adj(q.front())) {
			if(!m_comesFrom[adj]) {
				m_comesFrom[adj] = q.front();
				q.push(adj);
			}
		}
		q.pop();
	}
}

bool BreadthFirst::HasPath(int destination) const {
	if(destination == m_source) {
		return true;
	}
	return m_comesFrom[destination] != std::nullopt;
}

std::vector<int> BreadthFirst::TracePath(int destination) const {
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
