#pragma once

#include <memory>

#include "Geometry/Public/Node.h"

namespace Geometry {
namespace Index {

template <typename Value, size_t MinElements, size_t MaxElements>
class InsertVisitor {
	using Node = Detail::Node;
	using Leaf = Detail::Leaf<Value>;

public:
	InsertVisitor (Node& root, const Value& value, size_t depth, size_t relative_level)
		: root_(&root), value_(&value), depth_(depth), relative_level_(relative_level), level_(depth - relative_level) {
		assert(relative_level_ <= depth_);
		assert(level_ <= depth_);
	}

	void operator() (Leaf& leaf) {
		leaf.elements.emplace_back(value_);

		HandleOverflow(leaf);
	}

private:
	template <typename NodeType>
	void HandleOverflow (NodeType& node) {
		if (node.elements.size() > MaxElements) {
			Split(node);
		}
	}

	template <typename NodeType>
	void Split (NodeType& node) {
		std::unique_ptr<NodeType> second_node = std::make_unique<NodeType>();
		
		RedistributeElements(node, *second_node);
		assert(MinElements <= node.elements.size() && node.elements.size() <= MaxElements);
		assert(MinElements <= second_node->elements.size() && second_node->elements.size() <= MaxElements);

		// TODO
	}

	template <typename NodeType>
	void RedistributeElements (NodeType& node, NodeType& second_node) {
		using ElementsType = typename NodeType::ElementsType;
		using ElementType = typename ElementsType::value_type;

		ElementsType& elements1 = node.elements;
		ElementsType& elements2 = second_node.elements;
		assert(elements1.size() == MaxElements + 1);

		std::vector<ElementType> elements_copy(elements1.begin(), elements1.end());

		size_t seed1 = 0;
		size_t seed2 = 0;
		PickSeeds(elements_copy, seed1, seed2);
	}

	template <typename Elements>
	void PickSeeds (const Elements elements, size_t& seed1, size_t& seed2) {
		assert(elements.size() == MaxElements + 1);
		assert(2 <= elements.size());
	}

	Node* root_ = nullptr;
	const Value* value_ = nullptr;
	size_t depth_ = 0;
	size_t relative_level_ = 0;
	size_t level_ = 0;
};

} // namespace Index
} // namespace Geometry
