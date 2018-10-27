#pragma once

#include "Geometry/Public/Point.h"

namespace Geometry {
namespace Index {
namespace Detail {

template <typename Geometry>
struct IsIndexable {
	static const bool Value = false;
};

template <typename CoordinateType, std::size_t DimensionCount>
struct IsIndexable<Point<CoordinateType, DimensionCount>> {
	static const bool Value = true;
};

} // namespace Detail
} // namespace Index
} // namespace Geometry