#include "TernarySearchTrie.h"

namespace {

auto Size(const std::string& str) -> int {
	return static_cast<int>(str.size());
}

template<typename Val>
auto FindRec(const std::unique_ptr<Node<Val>>& node, const std::string& key, int depth) -> std::optional<Val> {
	if(!node) {
		return std::nullopt;
	}
	if(depth == Size(key)) {
		return node->val;
	}
	if(key[depth] == node->charac) {
		return FindRec(node->mid, key, depth + 1);
	}
	if(key[depth] < node->charac) {
		return FindRec(node->left, key, depth);
	} else {
		return FindRec(node->right, key, depth);
	}
} 


} // namespace

template<typename Val>
auto TernarySearchTrie<Val>::Find(const std::string& key) const -> std::optional<Val> {
	return FindRec(m_root, key, 0);
}

template class TernarySearchTrie<int>;
template struct Node<int>;