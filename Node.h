#pragma once

#include <vector>

namespace Geometry {

template <typename Value>
struct Leaf {
    std::vector<Value> elements;
};

} // namespace Geometry