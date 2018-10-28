#pragma once

namespace Geometry {
namespace Index {
namespace Traits {

template <typename Geometry>
struct Coordinate {
};

template <typename Geometry>
using CoordinateT = typename Coordinate<Geometry>::Type;

} // namespace Traits
} // namespace Index
} // namespace Geometry