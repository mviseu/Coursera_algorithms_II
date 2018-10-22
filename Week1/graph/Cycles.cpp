#include "Cycles.h"
#include <algorithm>
#include <iterator>
#include <memory>
#include <optional>
#include <iostream>

struct Reachability {
	Reachability(int nrVert) : visited(std::make_unique<std::vector<bool>>(nrVert, false)),
					 		   inVertices(std::make_unique<std::vector<std::vector<int>>>(nrVert, std::vector<int>())),
					 		   componentIds(std::make_unique<std::vector<std::optional<int>>>(nrVert, std::nullopt)) {} 
	std::unique_ptr<std::vector<bool>> visited;
	std::unique_ptr<std::vector<std::vector<int>>> inVertices;
	std::unique_ptr<std::vector<std::optional<int>>> componentIds;
};

auto Dfs(const DiGraph& gr, int v, const Reachability& reach, int id) -> void {
	for(auto e : gr.Adj(v)) {
		if(!(*reach.visited)[e]) {
			(*reach.visited)[e] = true;
			(*reach.componentIds)[e] = id;
			(*reach.inVertices)[e].push_back(v);
			Dfs(gr, e, reach, id);
		} else {
			if(id == *(*reach.componentIds)[e]) {
				(*reach.inVertices)[e].push_back(v);
			}
		}
	}
}

auto IsAlreadyInPath(int v, const std::vector<int>& path) -> bool {
	return std::find(path.cbegin(), path.cend(), v) != path.cend();
}

auto HasPotentialCycleBeenSeen(int prev, int curr) -> bool {
	return prev < curr;
}

auto Bdfs(int target, int v, const std::vector<std::vector<int>>& inVertices, 
		  const std::vector<int>& path, 
		  std::vector<std::vector<int>>& bdfs) -> void {
	for(auto comeFrom : inVertices[v]) {
			if(comeFrom == v) {
				continue;
			}
			if(comeFrom == target) {
				bdfs.push_back(path);
				continue;
			}
			if(IsAlreadyInPath(comeFrom, path) || HasPotentialCycleBeenSeen(comeFrom, target)) {
				continue;
			}
			auto newPath = path;
			newPath.push_back(comeFrom);
			Bdfs(target, comeFrom, inVertices, newPath, bdfs);
	}
}

auto RevertCycles(std::vector<std::vector<int>>&& cycles) -> std::vector<std::vector<int>> {
	for(auto& backCycle : cycles) {
		std::reverse(backCycle.begin(), backCycle.end());
	} 
	return std::move(cycles);
}


auto GetCycles(const DiGraph& gr) -> std::vector<std::vector<int>> {
	const auto nrVert = gr.V();
	auto reach = Reachability(nrVert);
	// first step is to mark all componentIds, inVertices with same Ids with dfs algorithm
	auto id = 0;
	for(auto v = 0; v < nrVert; ++v) {
		if(!(*reach.visited)[v]) {
			(*reach.visited)[v] = true;
			(*reach.componentIds)[v] = id;
			(*reach.inVertices)[v].push_back(v);
			Dfs(gr, v, reach, id);
			++id;
		}
	}
	// second step is to go through all invertices with dim > 1 and check for cycles
	auto bdfs = std::vector<std::vector<int>>();
	for(auto i = 0; i < nrVert; ++i) {
		if((*reach.inVertices)[i].size() > 1) {
			const auto path = std::vector<int>({i});
			Bdfs(i, i, *reach.inVertices, path, bdfs);
		}
	} 
	// revert all cycles to have them in correct direction
	return RevertCycles(std::move(bdfs));
}
