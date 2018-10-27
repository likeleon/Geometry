#pragma once

#include <vector>

namespace Geometry {
namespace Index {
namespace Detail {

struct Node {
	virtual ~Node () {
	}
};

template <typename Box>
struct InternalNode : public Node {
	using ElementType = std::pair<Box, Node*>;
	using ElementsType = std::vector<ElementType>;

	ElementsType elements;
};

template <typename Value>
struct Leaf : public Node {
	using ElementsType = std::vector<Value>;
	
	ElementsType elements;
};

} // namespace Detail
} // namespace Index
} // namespace Geometry