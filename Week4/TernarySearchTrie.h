#pragma once
#include <memory>
#include <optional>
#include <string>


template <typename Val>
struct Node {
	Node() = default;
	Node(char c) : charac(c) {}
	char charac = 'a';
	std::optional<Val> val = std::nullopt;
	std::unique_ptr<Node<Val>> left = nullptr;
	std::unique_ptr<Node<Val>> mid = nullptr;
	std::unique_ptr<Node<Val>> right = nullptr;
};


template <typename Val>
class TernarySearchTrie {
public:
	TernarySearchTrie() = default;
	auto Insert(const std::string& key, const Val& val) -> bool;
	//auto Erase(const std::string& key) -> void;
	auto Find(const std::string& key) const -> std::optional<Val>;

private:
	std::unique_ptr<Node<Val>> m_root = nullptr;
};

