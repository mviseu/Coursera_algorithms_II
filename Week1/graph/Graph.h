#pragma once
#include <vector>
#include <string>
#include <iostream>

class Graph {
public:
	explicit Graph(int V);
	explicit Graph(std::istream& is);
	explicit operator std::string() const;
	std::vector<int> Adj(int v) const;
	void AddEdge(int v, int w);
	int V() const;
	int E() const;
private:
	std::vector<std::vector<int>> adjacents;
};
