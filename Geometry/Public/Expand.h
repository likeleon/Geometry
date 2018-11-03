#pragma once

#include "Geometry/Public/Box.h"
#include "Geometry/Public/CoordinateDimension.h"
#include "Geometry/Public/CoordinateType.h"
#include "Geometry/Public/Point.h"
#include "Geometry/Public/Tag.h"
#include "Geometry/Public/Tags.h"

namespace Geometry {
namespace Index {

namespace Detail {

template <std::size_t Dimension, std::size_t DimensionCount>
struct PointLoop {
	template <typename Box, typename Point>
	static void Apply (Box& box, const Point& source) {
		using CoordinateType = typename CoordinateType<Point>::Type;

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

} // namespace Detail

namespace Dispatch {

template <
	typename GeometryOut,
	typename Geometry,
	typename TagOut = typename Tag<GeometryOut>::Type,
	typename Tag = typename Tag<Geometry>::Type
>
struct Expand {
};

template <typename BoxOut, typename Point>
struct Expand<BoxOut, Point, BoxTag, PointTag>
	: public Detail::PointLoop<0, Dimension<Point>::value> {
};

} // namespace Dispatch

template <typename GeometryOut, typename Geometry>
void Expand (GeometryOut& geometry_out, const Geometry& geometry) {
	Dispatch::Expand<GeometryOut, Geometry, typename Tag<GeometryOut>::Type, typename Tag<Geometry>::Type>
		::Apply(geometry_out, geometry);
};

} // namespace Index
} // namespace Geometry