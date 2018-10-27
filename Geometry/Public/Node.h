#pragma once

#include <vector>

namespace Geometry {
namespace Index {
namespace Detail {

template <typename Value>
struct Leaf {
	std::vector<Value> elements;
};

} // namespace Detail
} // namespace Index
} // namespace Geometry