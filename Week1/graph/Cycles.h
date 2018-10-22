#pragma once
#include "DiGraph.h"
#include <vector>

auto GetCycles(const DiGraph& gr) -> std::vector<std::vector<int>>;
