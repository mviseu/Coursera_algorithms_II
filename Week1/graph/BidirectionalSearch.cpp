#include "BidirectionalSearch.h"
#include <algorithm>
#include <deque>
#include <iostream>
#include <iterator>
#include <queue>

namespace {

enum struct Branch {source, dest};

struct Queued {
	Queued(int v, Branch b) : vertex(v), branch(b) {}
	int vertex = 0;
	Branch branch = Branch::source;
};

auto VisitAdjacent(int adj,  std::queue<Queued>& q, std::vector<std::optional<int>>& comesFrom1) -> void {
	if(!comesFrom1[adj]) {
		comesFrom1[adj] = q.front().vertex;
		q.push(Queued(adj, q.front().branch));
	}
}


auto BidirectionalSearch(const Graph& gr, std::queue<Queued>& q, std::vector<std::optional<int>>& s, std::vector<std::optional<int>>& d) -> std::optional<int> {
	while(!q.empty()) {
		const auto top = q.front();
		for(auto adj : gr.Adj(top.vertex)) {
			if(top.branch == Branch::source) {
				VisitAdjacent(adj, q, s);
				if(d[adj]) {
					return adj;
				}
			} else {
				VisitAdjacent(adj, q, d);
				if(s[adj]) {
					return adj;
				}
			}
		}
		q.pop();
	}
	return std::nullopt;
}

auto TracePath(int meet, const std::vector<std::optional<int>>& s, const std::vector<std::optional<int>> d) -> std::vector<int> {
	auto v = meet;
	auto path = std::deque<int>();
	while(v != *s[v]) {
		v = *s[v];
		path.push_front(v);
	}
	path.push_back(meet);
	v = meet;
	while(v != *d[v]) {
		v = *d[v];
		path.push_back(v);
	}
	auto vec = std::vector<int>(std::make_move_iterator(path.begin()), std::make_move_iterator(path.end()));
	return vec;
}

} // namespace


auto BidirectionalSearch(const Graph& gr, int source, int dest) -> std::optional<std::vector<int>> {
	if(source == dest) {
		return std::vector<int>({source});
	}
	auto q = std::queue<Queued>();
	auto comesFromS = std::vector<std::optional<int>>(gr.V(), std::nullopt), comesFromD = comesFromS;
	q.push(Queued(source, Branch::source));
	q.push(Queued(dest, Branch::dest));
	comesFromS[source] = source;
	comesFromD[dest] = dest;
	const auto ret = BidirectionalSearch(gr, q, comesFromS, comesFromD);
	return ret ? std::make_optional(TracePath(*ret, comesFromS, comesFromD)) : std::nullopt;
}

