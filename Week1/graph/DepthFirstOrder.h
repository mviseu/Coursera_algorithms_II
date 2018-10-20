#pragma once
#include "DiGraph.h"
#include <stack>
#include <vector>

class DepthFirstOrder {
public:
	explicit DepthFirstOrder(const DiGraph& gr);
	auto TopologicalSort() const -> std::vector<int>;

private:
	auto Dfs(const DiGraph& gr, int v) -> void;
	std::vector<bool> m_marked;
	std::stack<int> m_postOrder;
};