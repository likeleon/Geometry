#pragma once

#include <memory>
#include <tuple>
#include <utility>

#include "Geometry/Public/BoundedView.h"
#include "Geometry/Public/Content.h"
#include "Geometry/Public/Convert.h"
#include "Geometry/Public/Expand.h"
#include "Geometry/Public/Node.h"
#include "Math/Vec3.h"

namespace Geometry {
namespace Index {

namespace Detail {

template <typename Element, typename Value, size_t MinElements, size_t MaxElements>
class InsertVisitor {
protected:
	InsertVisitor (Detail::Node& root, const Element& element, size_t depth, size_t relative_level)
		: root_(&root), element_(&element), depth_(depth), relative_level_(relative_level), level_(depth - relative_level) {
		assert(relative_level_ <= depth_);
		assert(level_ <= depth_);
	}

	template <typename NodeType>
	void HandleOverflow (NodeType& node) {
		if (node.elements.size() > MaxElements) {
			Split(node);
		}
	}

	template <typename NodeType>
	void Split (NodeType& node) {
		Box box, box2;
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
		std::tie(seed1, seed2) = PickSeeds(elements_copy);

		// 노드의 요소들을 준비
		elements1.clear();
		assert(elements2.empty());

		elements1.push_back(elements_copy[seed1]);
		elements2.push_back(elements_copy[seed2]);

		// TODO
	}

	template <typename Elements>
	std::pair<size_t, size_t> PickSeeds (const Elements& elements) {
		using ElementType = typename Elements::value_type;
		using IndexableType = typename Detail::ElementIndexableType<ElementType>::Type;
		using BoundedIndexableView = Detail::BoundedView<IndexableType, Box>;

		assert(elements.size() == MaxElements + 1);
		assert(2 <= elements.size());

		long double greatest_free_content = 0;
		size_t seed1 = 0;
		size_t seed2 = 0;

		for (size_t i = 0; i < elements.size() - 1; ++i) {
			for (size_t j = i + 1; j < elements.size(); ++j) {
				const IndexableType& index1 = ElementIndexable(elements[i]);
				const IndexableType& index2 = ElementIndexable(elements[j]);

				Box enlarged_box;
				Index::Convert(index1, enlarged_box);

				Expand(enlarged_box, index2);

				BoundedIndexableView bounded_index1(index1);
				BoundedIndexableView bounded_index2(index2);
				
				long double free_content =
					Detail::Content(enlarged_box)
					- Detail::Content(bounded_index1)
					- Detail::Content(bounded_index2);

				if (greatest_free_content < free_content) {
					greatest_free_content = free_content;
					seed1 = i;
					seed2 = j;
				}
			}
		}

		return std::make_pair(seed1, seed2);
	}

	Detail::Node* root_ = nullptr;
	const Element* element_ = nullptr;
	size_t depth_ = 0;
	size_t relative_level_ = 0;
	size_t level_ = 0;
};

} // namespace Detail

template <typename Element, typename Value, size_t MinElements, size_t MaxElements>
class InsertVisitor : public Detail::InsertVisitor<Element, Value, MinElements, MaxElements> {
};

template <typename Value, size_t MinElements, size_t MaxElements>
class InsertVisitor<Value, Value, MinElements, MaxElements>
	: public Detail::InsertVisitor<Value, Value, MinElements, MaxElements> {
public:
	using Base = Detail::InsertVisitor<Value, Value, MinElements, MaxElements>;
	using Property = typename Value::second_type;
	
	InsertVisitor (Detail::Node& root, const Value& value, size_t depth, size_t relative_level)
		: Base(root, value, depth, relative_level) {
	}

	void operator() (Detail::Leaf<Property>& leaf) {
		std::pair<Math::Vec3, NoProperty> x = *Base::element_;
		leaf.elements.push_back(x);

		Base::HandleOverflow(leaf);
	}
};

} // namespace Index
} // namespace Geometry
