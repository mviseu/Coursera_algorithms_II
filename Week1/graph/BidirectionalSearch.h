#pragma once
#include "Graph.h"
#include <optional>
#include <vector>


auto BidirectionalSearch(const Graph& graph, int source, int dest) -> std::optional<std::vector<int>>;