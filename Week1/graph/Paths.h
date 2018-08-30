#pragma once
#include "Graph.h"
#include <optional>
#include <vector>

class Paths {
public:
	Paths(int source, const Graph& g);
	bool HasPath(int destination) const;
	std::vector<int> TracePath(int destination) const;

private:
	int m_source = 0;
	std::vector<std::optional<int>> m_comesFrom;
};

