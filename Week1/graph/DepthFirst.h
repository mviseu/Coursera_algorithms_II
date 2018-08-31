#pragma once
#include "Paths.h"
#include <optional>
#include <vector>

class DepthFirst : public Paths {
public:
	DepthFirst(int source, const Graph& g);
	bool HasPath(int destination) const override;
	std::vector<int> TracePath(int destination) const override;

private:
	int m_source = 0;
	std::vector<std::optional<int>> m_comesFrom;
};

