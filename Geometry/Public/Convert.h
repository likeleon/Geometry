#pragma once

#include "Geometry/Public/Access.h"
#include "Geometry/Public/CoordinateDimension.h"
#include "Geometry/Public/CoordinateType.h"
#include "Geometry/Public/Tag.h"
#include "Geometry/Public/Tags.h"

namespace Geometry {
namespace Index {

namespace Detail {

template <typename Point, typename Box, std::size_t Index, std::size_t Dimension, std::size_t DimensionCount>
struct PointToBox {
	static void Apply (const Point& point, Box& box) {
		using CoordinateType = typename CoordinateType<Box>::Type;

		auto x = Get<Dimension>(point);
		Set<Index, Dimension>(box, x);

		PointToBox<Point, Box, Index, Dimension + 1, DimensionCount>::Apply(point, box);
	}
};

template <typename Point, typename Box, std::size_t Index, std::size_t DimensionCount>
struct PointToBox<Point, Box, Index, DimensionCount, DimensionCount> {
	static void Apply (const Point& /*point*/, Box& /*box*/) {
	}
};

template <
	typename Geometry1, 
	typename Geometry2, 
	typename Tag1 = typename Tag<Geometry1>::Type,
	typename Tag2 = typename Tag<Geometry2>::Type,
	std::size_t DimensionCount = Dimension<Geometry1>::value
>
struct Convert {
};

template <typename Geometry1, typename Geometry2, typename Tag, std::size_t DimensionCount>
struct Convert<Geometry1, Geometry2, Tag, Tag, DimensionCount> {
	static void Apply (const Geometry1& source, Geometry2& destination) {
		destination = source;
	}
};

template <typename Point, typename Box, std::size_t DimensionCount>
struct Convert<Point, Box, PointTag, BoxTag, DimensionCount> {
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