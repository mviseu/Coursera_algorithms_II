#include "Trie.h"
#include <iostream>
#include <tuple>
#include <utility>

namespace {

int GetBase() {
	return static_cast<int>('a');
}

int GetIndex(char c) {
	return static_cast<int>(c) - GetBase();
}

char GetChar(int index) {
	return static_cast<char>(index + GetBase());
}

int Size(const std::string& str) {
	return static_cast<int>(str.size());
}

template <typename Val, int R>
bool HasAnyChild(const Node<Val, R>& node) {
	return std::any_of(node.next.cbegin(), node.next.cend(), [](const std::unique_ptr<Node<Val, R>>& link) {
		return link != nullptr;
	});
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

template <typename Val, int R>
void KeysRec(const Node<Val, R>& node, std::vector<std::string>& keys, const std::string& word) {
	for(auto i = 0; i < R; ++i) {
		if(!node.next[i]) {
			continue;
		}
		const auto newWord = word + GetChar(i);
		if(node.next[i]->val) {
			keys.push_back(newWord);
		}
		KeysRec(*node.next[i], keys, newWord);
	}
}


template <typename Val, int R>
std::unique_ptr<Node<Val, R>> EraseRec(std::unique_ptr<Node<Val, R>> node, const std::string& key, int depth) {
	if(node == nullptr) {
		return std::move(node);
	}
	if(depth == Size(key)) {
		node->val = std::nullopt;
	} else {
		const auto charact = key[depth];
		const auto index = GetIndex(charact);
		node->next[index] = EraseRec(std::move(node->next[index]), key, depth + 1);
	}
	if(node->val == std::nullopt && !HasAnyChild(*node)) {
		return nullptr;
	}
	return std::move(node);
}

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


template <typename Val, int R>
void Trie<Val, R>::Erase(const std::string& key) {
	m_root = EraseRec(std::move(m_root), key, 0);
}


template <typename Val, int R>
std::vector<std::string> Trie<Val, R>::Keys() const {
	std::vector<std::string> keys;
	if(m_root) {
		KeysRec(*m_root, keys, "");
	}
	return keys;
}

template class Trie<int, NrAlpha>;
template struct Node<int, NrAlpha>;

