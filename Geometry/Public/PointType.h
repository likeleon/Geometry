#pragma once

namespace Geometry {
namespace Index {

namespace Traits {

template <typename Geometry>
struct PointType {
};

} // namespace Traits

template <typename GeometryTag, typename Geometry>
struct PointType {
	using Type = typename Traits::PointType<Geometry>::Type;
};

} // namespace Index
} // namespace Geometry