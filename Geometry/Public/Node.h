#pragma once

#include <vector>

namespace Geometry {
namespace Index {
namespace Detail {

struct Node {
	virtual ~Node () {
	}
};

struct InternalNode : public Node {
	using ElementType = Node*;
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