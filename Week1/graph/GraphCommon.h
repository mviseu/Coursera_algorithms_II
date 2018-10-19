#pragma once
#include <vector>
#include <iostream>

auto ReadNrVertices(std::istream& is) -> int;

auto ReadNrEdges(std::istream& is) -> int;

auto ReadOutEdges(std::istream& is, int nrEdges) -> std::vector<std::pair<int, int>>;

auto CreateEmptyGraph(int v) -> std::vector<std::vector<int>>;

auto AddOutEdge(std::vector<std::vector<int>>& outEdges, int from, int to) -> void;

auto PrintEdges(std::ostream& os, const std::vector<std::vector<int>>& outEdges) -> std::ostream&;

auto GetOutEdges(const std::vector<std::vector<int>>& outEdges, int v) -> std::vector<int>;

auto CountVertices(const std::vector<std::vector<int>>& outEdges) -> int;

auto CountEdges(const std::vector<std::vector<int>>& outEdges) -> int;