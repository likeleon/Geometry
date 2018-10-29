#pragma once

#include <vector>

#include "Geometry/Public/Translator.h"

namespace Geometry {
namespace Index {
namespace Detail {

struct Node {
	virtual ~Node () {
	}
};

template <typename Box>
struct InternalNode : public Node {
	using ElementType = std::pair<Box, std::unique_ptr<Node>>;
	using ElementsType = std::vector<ElementType>;

	ElementsType elements;
};

template <typename Value>
struct Leaf : public Node {
	using ElementsType = std::vector<Value>;
	
	ElementsType elements;
};

template <typename Element, typename Translator>
struct ElementIndexableType {
	using Type = typename IndexableType<Translator>::Type;
};

template <typename Element, typename Translator>
ResultTypeT<Translator> ElementIndexable (const Element& element, const Translator& translator) {
	return translator(element);
}

} // namespace Detail
} // namespace Index
} // namespace Geometry