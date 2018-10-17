#include "ConnectedComponents.h"

namespace {

auto Dfs(const Graph& gr, std::vector<std::optional<int>>& ids, int source) -> void {
	for(auto a : gr.Adj(source)) {
		if(!ids[a]) {
			ids[a] = ids[source];
			Dfs(gr, ids, a);
		}
	}
}

} // namespace


ConnectedComponents::ConnectedComponents(const Graph& gr) : m_id(std::vector<std::optional<int>>(gr.V(), std::nullopt)) {
	for(auto s = 0; s < gr.V(); ++s) {
		if(!m_id[s]) {
			m_id[s] = m_count;
			Dfs(gr, m_id, s);
			++m_count;
		}
	}
}

auto ConnectedComponents::Connected(int v1, int v2) const -> bool {
	return m_id[v1] == m_id[v2];
}

auto ConnectedComponents::Count() const -> int {
	return m_count;
}

auto ConnectedComponents::Id(int v) const -> std::optional<int> {
	return m_id[v];
}
