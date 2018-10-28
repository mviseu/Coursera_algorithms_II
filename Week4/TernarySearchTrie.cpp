#include "TernarySearchTrie.h"
#include <tuple>

namespace {

auto Size(const std::string& str) -> int {
	return static_cast<int>(str.size());
}

template<typename Val>
auto InsertRec(std::unique_ptr<Node<Val>> node, const std::string& key, const Val& val, int depth) -> std::pair<bool, std::unique_ptr<Node<Val>>> {
	if(!node) {
		node = std::make_unique<Node<Val>>(key[depth]);
	}
	if(depth + 1 == Size(key)) {
		if(key[depth] == node->charac) {
			if(node->val) {
				return std::make_pair(false, std::move(node));
			} else {
				node->val = val;
				return std::make_pair(true, std::move(node));
			}
		}
	}
	auto inserted = false;
	if(key[depth] == node->charac) {
		std::tie(inserted, node->mid) = InsertRec(std::move(node->mid), key, val, depth + 1);
	} else {
		if(key[depth] < node->charac) {
			std::tie(inserted, node->left) = InsertRec(std::move(node->left), key, val, depth);
		} else {
			std::tie(inserted, node->right) = InsertRec(std::move(node->right), key, val, depth);
		}
	}
	return std::make_pair(inserted, std::move(node));
} 

template<typename Val>
auto FindRec(const std::unique_ptr<Node<Val>>& node, const std::string& key, int depth) -> std::optional<Val> {
	if(!node) {
		return std::nullopt;
	}
	if(depth + 1 == Size(key)) {
		if(key[depth] == node->charac)  {
			return node->val;
		}
	}
	if(key[depth] == node->charac)  {
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
auto TernarySearchTrie<Val>::Insert(const std::string& key, const Val& val) -> bool {
	if(key.empty()) {
		return false;
	}
	auto inserted = false;
	std::tie(inserted, m_root) = InsertRec(std::move(m_root), key, val, 0);
	return inserted;
}

template<typename Val>
auto TernarySearchTrie<Val>::Find(const std::string& key) const -> std::optional<Val> {
	if(key.empty()) {
		return std::nullopt;
	}
	return FindRec(m_root, key, 0);
}

template class TernarySearchTrie<int>;
template struct Node<int>;