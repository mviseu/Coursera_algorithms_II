#pragma once
#include <vector>
#include <ostream>


auto AddOutEdge(std::vector<std::vector<int>>& outEdges, int from, int to) -> void;

auto PrintEdges(std::ostream& os, const std::vector<std::vector<int>>& outEdges) -> std::ostream&;

auto GetOutEdges(const std::vector<std::vector<int>>& outEdges, int v) -> std::vector<int>;

auto CountVertices(const std::vector<std::vector<int>>& outEdges) -> int;

auto CountEdges(const std::vector<std::vector<int>>& outEdges) -> int;