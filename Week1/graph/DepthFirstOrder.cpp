#include "DepthFirstOrder.h"


DepthFirstOrder::DepthFirstOrder(const DiGraph& gr) : m_marked(std::vector<bool>(gr.V(), false)) {
	for(auto v = 0; v < gr.V(); ++v) {
		Dfs(gr, v);
	}
}

auto DepthFirstOrder::Dfs(const DiGraph& gr, int v) -> void {
	if(!m_marked[v]) {
		m_marked[v] = true;
		for(auto edge : gr.Adj(v)) {
			Dfs(gr, edge);
		}
		m_postOrder.push(v);
	}
}

auto DepthFirstOrder::TopologicalSort() const -> std::vector<int> {
	auto stack = m_postOrder;
	auto postOrder = std::vector<int>();
	while(!stack.empty()) {
		postOrder.push_back(stack.top());
		stack.pop();
	}
	return postOrder;
}