#pragma once

#include "Geometry/Public/CoordinateType.h"
#include "Geometry/Public/Tag.h"
#include "Geometry/Public/Tags.h"

namespace Geometry {
namespace Index {
namespace Detail {

template <
	typename Geometry,
	typename BoundingGeometry,
	typename Tag = typename Index::Tag<Geometry>::type,
	typename Bounding = typename Index::Tag<BoundingGeometry>::Type
>
class BoundedView {
};

template <typename Point, typename Box>
class BoundedView<Point, Box, PointTag, BoxTag> {
public:
	using CoordinateType = typename CoordinateType<Box>::Type;

	explicit BoundedView (const Point& point)
		: point_(&point) {
	}

	template <std::size_t Dimension>
	CoordinateType GetMin () const {
		return Get<Dimension>(*point_);
	}

	template <std::size_t Dimension>
	CoordinateType GetMan () const {
		return Get<Dimension>(*point_);
	}

private:
	const Point* point_ = nullptr;
};

} // namespace Detail
} // namespace Index
} // namespace Geometry
