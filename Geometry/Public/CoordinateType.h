#pragma once

#include "Geometry/Public/PointType.h"
#include "Geometry/Public/Tag.h"
#include "Geometry/Public/Tags.h"

namespace Geometry {
namespace Index {

namespace Traits {

template <typename Geometry>
struct CoordinateType {
};

} // namespace Traits

namespace CoreDispatch {

template <typename GeometryTag, typename Geometry>
struct CoordinateType {
	using PointType = typename PointType<GeometryTag, Geometry>::Type;
	using Type = typename CoordinateType<PointTag, PointType>::Type;
};

template <typename Point>
struct CoordinateType<PointTag, Point> {
	using Type = typename Traits::CoordinateType<Point>::Type;
};

} // namespace CoreDispatch

template <typename Geometry>
struct CoordinateType {
	using Type = typename CoreDispatch::CoordinateType<typename Tag<Geometry>::Type, Geometry>::Type;
};

} // namespace Index
} // namespace Geometry