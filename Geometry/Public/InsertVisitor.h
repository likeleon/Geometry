#pragma once

#include <memory>
#include <tuple>
#include <utility>

#include "Geometry/Public/Convert.h"
#include "Geometry/Public/Expand.h"
#include "Geometry/Public/Node.h"
#include "Geometry/Public/Translator.h"

namespace Geometry {
namespace Index {

namespace Detail {

template <typename Translator>
struct ElementIndexableType {
	using Type = typename IndexableType<Translator>::Type;
};

template <typename Translator>
using ElementIndexableTypeT = typename ElementIndexableType<Translator>::Type;

} // namespace Detail

template <typename Value, size_t MinElements, size_t MaxElements, typename Translator, typename Box>
class InsertVisitor {
private:
	using IndexableType = Detail::ElementIndexableTypeT<Translator>;
	using Node = Detail::Node;
	using Leaf = Detail::Leaf<Value>;

public:
	InsertVisitor (Node& root, const Value& value, size_t depth, size_t relative_level, const Translator& translator)
		: root_(&root), value_(&value), depth_(depth), relative_level_(relative_level), 
		  level_(depth - relative_level), translator_(&translator) {
		assert(relative_level_ <= depth_);
		assert(level_ <= depth_);
	}

	void operator() (Leaf& leaf) {
		leaf.elements.push_back(*value_);

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
		//Box box, box2;
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

		// 원본 요소들을 복사
		std::vector<ElementType> elements_copy(elements1.begin(), elements1.end());
		std::vector<ElementType> elements_backup(elements1.begin(), elements1.end());

		// 초기 시드값을 계산
		size_t seed1;
		size_t seed2;
		std::tie(seed1, seed2) = PickSeeds<Box>(elements_copy);

		// 노드의 요소들을 준비
		elements1.clear();

		elements1.push_back(elements_copy[seed1]);
		elements1.push_back(elements_copy[seed2]);
	}

	template <typename Box, typename Elements>
	std::pair<size_t, size_t> PickSeeds (const Elements elements) {
		long double greatest_free_content = 0;
		size_t seed1 = 0;
		size_t seed2 = 0;

		assert(elements.size() == MaxElements + 1);
		assert(2 <= elements.size());

		for (size_t i = 0; i < elements.size() - 1; ++i) {
			for (size_t j = i + 1; j < elements.size(); ++j) {
				const IndexableType& index1 = Detail::ElementIndexable(elements[i], *translator_);
				const IndexableType& index2 = Detail::ElementIndexable(elements[j], *translator_);

				Box enlarged_box;
				Convert(index1, enlarged_box);

				Expand(enlarged_box, index2);

				// TODO
			}
		}

		return std::make_pair(seed1, seed2);
	}

	Node* root_ = nullptr;
	const Value* value_ = nullptr;
	size_t depth_ = 0;
	size_t relative_level_ = 0;
	size_t level_ = 0;
	const Translator* translator_ = nullptr;
};

} // namespace Index
} // namespace Geometry
