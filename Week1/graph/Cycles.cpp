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


auto GetCycles(const DiGraph& gr) -> void {
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
	std::cout << "components" << std::endl;
	for(const auto& id : *reach.componentIds) {
		std::cout << *id << std::endl;
	}

	std::cout << "inVertices" << std::endl;
	std::ostream_iterator<int> out(std::cout, " ");
	for(const auto& in : *reach.inVertices) {
		std::copy(in.begin(), in.end(), out);
		std::cout << std::endl;
	}
}
