#pragma once
#include <algorithm>
#include <memory>
#include <optional>
#include <string>
#include <vector>

constexpr const auto NrAlpha = 26;

template <typename Val, int R>
struct Node {
	Node() {
		std::generate_n(std::back_inserter(next), R, []() {
			return nullptr;
		});
	}
	std::optional<Val> val = std::nullopt;
	std::vector<std::unique_ptr<Node<Val, R>>> next;
};


template <typename Val, int R>
class Trie {
public:
	Trie() = default;
	bool Insert(const std::string& key, const Val& val);
	void Erase(const std::string& key);
	std::optional<Val> Find(const std::string& key) const;
	std::vector<std::string> Keys() const;

private:
	std::unique_ptr<Node<Val, R>> m_root = nullptr;
};

