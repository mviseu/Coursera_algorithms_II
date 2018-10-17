#pragma once
#include "Graph.h"
#include <optional>
#include <vector>


class ConnectedComponents {
public:
	explicit ConnectedComponents(const Graph& gr);
	bool Connected(int v1, int v2) const;
	int Count() const;
	std::optional<int> Id(int v) const;
private:
	int m_count = 0;
	std::vector<std::optional<int>> m_id;
};