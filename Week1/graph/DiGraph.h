#pragma once
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
private:
	std::vector<std::vector<int>> m_outEdges;
};
