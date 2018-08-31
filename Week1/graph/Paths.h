#pragma once
#include "Graph.h"
#include <vector>

class Paths {
public:
	virtual ~Paths() = default;
	virtual bool HasPath(int destination) const = 0;
	virtual std::vector<int> TracePath(int destination) const = 0;
};
