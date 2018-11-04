#pragma once

#include <vector>

#include "Geometry/Public/Box.h"
#include "Math/Vec3.h"

namespace Geometry {
namespace Index {
namespace Detail {

struct Node {
	virtual ~Node () {
	}
};

struct InternalNode : public Node {
	using ElementType = std::pair<Box, Node*>;
	using ElementsType = std::vector<ElementType>;

	ElementsType elements;
};

template <typename Property>
struct Leaf : public Node {
	using ElementType = std::pair<Math::Vec3, Property>;
	using ElementsType = std::vector<ElementType>;

	ElementsType elements;
};

template <typename Element>
struct ElementIndexableType {
};

template <typename Property>
struct ElementIndexableType<std::pair<Math::Vec3, Property>> {
	using Type = Math::Vec3;
};
template <>
struct ElementIndexableType<std::pair<Box, Node*>> {
	using Type = Box;
};

template <typename Property>
const Math::Vec3& ElementIndexable (const std::pair<Math::Vec3, Property>& value) {
	return value.first;
}

const Box& ElementIndexable (const std::pair<Box, Node>& pair) {
	return pair.first;
}

} // namespace Detail
} // namespace Index
} // namespace Geometry