#pragma once

#include "Geometry/Public/CoordinateDimension.h"
#include "Geometry/Public/CoordinateType.h"
#include "Geometry/Public/Box.h"
#include "Geometry/Public/Point.h"

namespace Geometry {
namespace Index {

namespace Detail {

template <std::size_t Dimension, std::size_t DimensionCount>
struct PointLoop {
	template <typename Box, typename Point>
	static void Apply (Box& box, const Point& source) {
		using CoordinateType = Traits::CoordinateT<Point>;

		std::less<CoordinateType> less;
		std::greater<CoordinateType> greater;

		CoordinateType coord = Get<Dimension>(source);

		if (less(coord, Get<0, Dimension>(box))) {
			Set<0, Dimension>(box, coord);
		}

		if (greater(coord, Get<1, Dimension>(box))) {
			Set<1, Dimension>(box, coord);
		}

		PointLoop<Dimension + 1, DimensionCount>::Apply(box, source);
	}
};

template <std::size_t DimensionCount>
struct PointLoop<DimensionCount, DimensionCount> {
	template <typename Box, typename Point>
	static void Apply (Box& /*box*/, const Point& /*source*/) {
	}
};

template <typename BoxOut, typename Point>
struct Expand : PointLoop<0, Traits::Dimension<Point>::value> {
};

} // namespace Detail

template <typename GeometryOut, typename Geometry>
void Expand (GeometryOut& geometry_out, const Geometry& geometry) {
	Detail::Expand<GeometryOut, Geometry>::Apply(geometry_out, geometry);
};

} // namespace Index
} // namespace Geometry