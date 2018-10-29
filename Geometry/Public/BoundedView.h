#pragma once

#include "Geometry/Public/Box.h"
#include "Geometry/Public/CoordinateType.h"
#include "Geometry/Public/Point.h"

namespace Geometry {
namespace Index {
namespace Detail {

template <typename Geometry, typename Box>
class BoundedView {
};

template <typename CoordinateType, std::size_t DimensionCount>
class BoundedView<Point<CoordinateType, DimensionCount>, Box<Point<CoordinateType, DimensionCount>>> {
public:
	explicit BoundedView (const Point<CoordinateType, DimensionCount>& point)
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
	const Point<CoordinateType, DimensionCount>* point_ = nullptr;
};

} // namespace Detail
} // namespace Index
} // namespace Geometry
