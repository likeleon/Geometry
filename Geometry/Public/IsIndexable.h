#pragma once

#include "Geometry/Public/Tag.h"
#include "Geometry/Public/Tags.h"

namespace Geometry {
namespace Index {
namespace Detail {

template <typename Geometry, typename Tag = typename Tag<Geometry>::Type>
struct IsIndexable {
	static const bool Value = false;
};

template <typename Point>
struct IsIndexable<Point, PointTag> {
	static const bool Value = true;
};

} // namespace Detail
} // namespace Index
} // namespace Geometry