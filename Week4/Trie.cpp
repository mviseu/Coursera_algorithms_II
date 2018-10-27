#include "Trie.h"
#include <iostream>
#include <tuple>
#include <utility>

namespace {

int GetIndex(char c) {
	const auto base = static_cast<int>('a');
	return static_cast<int>(c - base);
}

int Size(const std::string& str) {
	return static_cast<int>(str.size());
}

template <typename Val, int R>
std::pair<bool, std::unique_ptr<Node<Val, R>>> InsertRec(std::unique_ptr<Node<Val, R>> node, 
					   									 const std::string& key,
					   									 const Val& val,
					   									 int depth) {
	if(node == nullptr) {
		node = std::make_unique<Node<Val, R>>();
	}
	if(depth == Size(key)) {
		if(node->val) {
			return std::make_pair(false, std::move(node));			
		} else {
			node->val = val;
			return std::make_pair(true, std::move(node));				
		}
	}
	const auto charact = key[depth];
	const auto index = GetIndex(charact);
	auto inserted = false;
	std::tie(inserted, node->next[index]) = InsertRec(std::move(node->next[index]), key, val, depth + 1);
	return std::make_pair(inserted, std::move(node));
}

template <typename Val, int R>
std::optional<Val> FindRec(const Node<Val, R>& node, const std::string& key, int depth) {
	if(depth == Size(key)) {
		return node.val;
	}
	const auto charact = key[depth];
	const auto index = GetIndex(charact);
	return node.next[index] != nullptr ? FindRec(*node.next[index], key, depth + 1) : std::nullopt;
}

/*
template <typename Val, int R>
bool EraseRec(const Node<Val, R>& node, const std::string& key, int depth) {
	if(key.size() == depth) {
		return node.val;
	}
	const auto charact = key[depth];
	return node.next[charact] != nullptr ? FindRec(*node.next[charact], key, depth + 1) : std::nullopt;
}
*/

} // namespace

template <typename Val, int R>
bool Trie<Val, R>::Insert(const std::string& key, const Val& val) {
	auto isInserted = false;
	std::tie(isInserted, m_root) = InsertRec(std::move(m_root), key, val, 0);
	return isInserted;
}


template <typename Val, int R>
std::optional<Val> Trie<Val, R>::Find(const std::string& key) const {
	return m_root != nullptr ? FindRec(*m_root, key, 0) : std::nullopt;
}

template class Trie<int, NrAlpha>;
template struct Node<int, NrAlpha>;

/*

template <typename Val, int R>
bool Trie<Val, R>::Erase(const std::string& key) {
	return m_root != nullptr ? EraseRec(*m_root, key, 0) : false;
}
*/

