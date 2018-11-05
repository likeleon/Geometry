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

		RedistributeElements(node, *second_node, box, box2);
		assert(MinElements <= node.elements.size() && node.elements.size() <= MaxElements);
		assert(MinElements <= second_node->elements.size() && second_node->elements.size() <= MaxElements);

		// TODO
	}

	template <typename NodeType>
	void RedistributeElements (NodeType& node, NodeType& second_node, Box& box1, Box& box2) {
		using ElementsType = typename NodeType::ElementsType;
		using ElementType = typename ElementsType::value_type;
		using IndexableType = typename ElementIndexableType<ElementType>::Type;

		ElementsType& elements1 = node.elements;
		ElementsType& elements2 = second_node.elements;
		assert(elements1.size() == MaxElements + 1);

		// 원본 요소들을 복사
		std::vector<ElementType> elements_copy(elements1.begin(), elements1.end());

		// 초기 시드값을 계산
		size_t seed1;
		size_t seed2;
		std::tie(seed1, seed2) = PickSeeds(elements_copy);

		// 노드의 요소들을 준비
		elements1.clear();
		assert(elements2.empty());

		// 시드들을 추가
		elements1.push_back(elements_copy[seed1]);
		elements2.push_back(elements_copy[seed2]);

		// 박스 계산
		Index::Convert(ElementIndexable(elements_copy[seed1]), box1);
		Index::Convert(ElementIndexable(elements_copy[seed2]), box2);

		// 시드 삭제
		MoveFromBack(elements_copy, elements_copy.begin() + seed2);
		elements_copy.pop_back();
		MoveFromBack(elements_copy, elements_copy.begin() + seed1);
		elements_copy.pop_back();

		// 영역 초기화
		long double content1 = Content(box1);
		long double content2 = Content(box2);

		size_t remaining = elements_copy.size();

		// 나머지 엘리먼트들도 재분배
		while (!elements_copy.empty()) {
			auto it = elements_copy.rbegin();
			bool insert_into_group1 = false;

			size_t elements1_count = elements1.size();
			size_t elements2_count = elements2.size();

			if (elements1_count + remaining <= MinElements) {
				insert_into_group1 = true;
			} else if (elements2_count + remaining <= MinElements) {
				insert_into_group1 = false;
			} else {
				// TODO
			}

			// 선택된 그룹으로 엘리먼트를 이동
			const ElementType& element = *it;
			const IndexableType& indexable = ElementIndexable(element);

			if (insert_into_group1) {
				elements1.push_back(element);
				Expand(box1, indexable);
				content1 = Content(box1);
			} else {
				elements2.push_back(element);
				Expand(box2, indexable);
				content2 = Content(box2);
			}

			MoveFromBack(elements_copy, it.base() - 1);
			elements_copy.pop_back();

			--remaining;
		}
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
		size_t seed2 = 1;

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
