#pragma once
#include <optional>
#include <vector>
#include <string>
#include <iostream>

class DiGraph {
public:
	explicit DiGraph(int V);
	explicit DiGraph(std::istream& is);
	explicit operator std::string() const;
	auto Adj(int v) const -> std::vector<int>;
	auto AddEdge(int v, int w) -> void;
	auto V() const -> int;
	auto E() const -> int;
	auto Cycles() const -> std::vector<std::vector<int>> const;
	auto IsCyclic() const -> bool;
private:
	auto Dfs(int vert, 
			 std::vector<std::optional<int>>& comesFrom,
			 std::vector<int>& endCycles) const -> void;
	std::vector<std::vector<int>> m_outEdges;
};
