#pragma once

#include "Geometry/Public/Access.h"
#include "Geometry/Public/Point.h"
#include "Geometry/Public/Box.h"

namespace Geometry {
namespace Index {

namespace Detail {

template <typename Point, typename Box, std::size_t Index, std::size_t Dimension, std::size_t DimensionCount>
struct PointToBox {
	static void Apply (const Point& point, Box& box) {
		using CoordinateType = Traits::CoordinateT<Point>;

		Set<Index, Dimension>(box, Get<Dimension>(point));

		PointToBox<Point, Box, Index, Dimension + 1, DimensionCount>::Apply(point, box);
	}
};

template <typename Point, typename Box, std::size_t Index, std::size_t DimensionCount>
struct PointToBox<Point, Box, Index, DimensionCount, DimensionCount> {
	static void Apply (const Point& /*point*/, Box& /*box*/) {
	}
};

template <typename Geometry1, typename Geometry2>
struct Convert;

template <typename CoordinateType, std::size_t DimensionCount>
struct Convert<Point<CoordinateType, DimensionCount>, Box<Point<CoordinateType, DimensionCount>>> {
	using Point = Point<CoordinateType, DimensionCount>;
	using Box = Box<Point>;

	static void Apply (const Point& point, Box& box) {
		PointToBox<Point, Box, 0, 0, DimensionCount>::Apply(point, box);
		PointToBox<Point, Box, 1, 0, DimensionCount>::Apply(point, box);
	}
};

} // namespace Detail

template <typename Geometry1, typename Geometry2>
void Convert (const Geometry1& geometry1, Geometry2& geometry2) {
	Detail::Convert<Geometry1, Geometry2>::Apply(geometry1, geometry2);
}

} // namespace Index
} // namespace Geometry