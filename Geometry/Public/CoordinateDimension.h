#pragma once

namespace Geometry {
namespace Index {

namespace Traits {

template <typename Point>
struct Dimension {
};

} // namespace Traits

template <typename Point>
struct Dimension : Traits::Dimension<Point> {
};

} // namespace Index
} // namespace Geometry