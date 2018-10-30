#pragma once
#include <algorithm>
#include <memory>
#include <optional>
#include <string>
#include <vector>

template <typename Val, int R> struct Node;
template <typename Val, int R> class Trie;

namespace {
template <typename Val, int R>
void GenerateNext(std::vector<std::unique_ptr<Node<Val, R>>>& lhs, const std::vector<std::unique_ptr<Node<Val, R>>>& rhs) {
	auto i = -1;
	std::generate_n(std::back_inserter(lhs), R, [&i, &rhs]() {
		++i;
		if(rhs[i]) {
			return std::make_unique<Node<Val, R>>(*rhs[i]);
		} else {
			return std::unique_ptr<Node<Val, R>>();
		}
	});	
}

template <typename Val, int R>
void CopyRoot(std::unique_ptr<Node<Val, R>>& lhs, const std::unique_ptr<Node<Val, R>>& rhs) {
	if(rhs) {
		lhs = std::make_unique<Node<Val, R>>(*rhs);
	} else {
		lhs = nullptr;
	}
}

}

constexpr const auto NrAlpha = 26;

template <typename Val, int R>
struct Node {
	Node() {
		std::generate_n(std::back_inserter(next), R, []() {
			return nullptr;
		});
	}
	Node(const Node& rhs) : val(rhs.val) {
		GenerateNext(next, rhs.next);
	}
	Node(Node&& rhs) noexcept : val(std::move(rhs.val)), next(std::move(rhs.next)) {}
	Node& operator=(const Node& rhs) {
		if(this != &rhs) {
			val = rhs.val;
			next = std::vector<std::unique_ptr<Node<Val, R>>>();
			GenerateNext(next, rhs.next);
		}
		return *this;
	}
	Node& operator=(Node&& rhs) noexcept {
		if(this != &rhs) {
			val = std::move(rhs.val);
			next = std::move(rhs.next);
		}
		return *this;
	}
	std::optional<Val> val = std::nullopt;
	std::vector<std::unique_ptr<Node<Val, R>>> next;
};


template <typename Val, int R>
class Trie {
public:
	Trie() = default;
	Trie(const Trie& rhs) {
		CopyRoot(m_root, rhs.m_root);
	}
	Trie(Trie && rhs) noexcept : m_root(std::move(rhs.m_root)) {}
	Trie& operator=(const Trie& rhs) {
		if(this != &rhs) {
			CopyRoot(m_root, rhs.m_root);
		}
		return *this;
	}
	Trie& operator=(Trie&& rhs) noexcept {
		if(this != &rhs) {
			m_root = std::move(rhs.m_root);
		}
		return *this;	
	}
	bool Insert(const std::string& key, const Val& val);
	void Erase(const std::string& key);
	std::optional<Val> Find(const std::string& key) const;
	std::vector<std::string> Keys() const;
	//std::vector<std::string> KeysWithPrefix(const std::string& prefix) const;

private:
	std::unique_ptr<Node<Val, R>> m_root = nullptr;
};

