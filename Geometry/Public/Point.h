#pragma once

#include <cstddef>

#include "Geometry/Public/Access.h"
#include "Geometry/Public/CoordinateType.h"
#include "Geometry/Public/CoordinateDimension.h"
#include "Geometry/Public/Tag.h"
#include "Geometry/Public/Tags.h"

namespace Geometry {
namespace Index {

namespace Detail {

template <std::size_t DimensionCount, std::size_t Index>
struct ArrayAssign {
	template <typename T>
	static void Apply(T values[], const T& value) {
		values[Index] = value;
	}
};

template <>
struct ArrayAssign<2, 2> {
	template <typename T>
	static void Apply(T[], const T&) {
	}
};

template <>
struct ArrayAssign<1, 1> {
	template <typename T>
	static void Apply(T[], const T&) {
	}
};

template <>
struct ArrayAssign<1, 2> {
	template <typename T>
	static void Apply(T[], const T&) {
	}
};

} // namespace Detail

template <typename CoordinateType, std::size_t DimensionCount>
class Point {
	static_assert(DimensionCount >= 1, "Dimension greater than zero expected");

public:
	Point () = default;

	explicit Point (const CoordinateType& v0) {
		Detail::ArrayAssign<DimensionCount, 0>::Apply(values_, v0);
		Detail::ArrayAssign<DimensionCount, 1>::Apply(values_, CoordinateType());
		Detail::ArrayAssign<DimensionCount, 2>::Apply(values_, CoordinateType());
	}

	explicit Point (const CoordinateType& v0, const CoordinateType& v1) {
		Detail::ArrayAssign<DimensionCount, 0>::Apply(values_, v0);
		Detail::ArrayAssign<DimensionCount, 1>::Apply(values_, v1);
		Detail::ArrayAssign<DimensionCount, 2>::Apply(values_, CoordinateType());
	}

	explicit Point (const CoordinateType& v0, const CoordinateType& v1, const CoordinateType& v2) {
		Detail::ArrayAssign<DimensionCount, 0>::Apply(values_, v0);
		Detail::ArrayAssign<DimensionCount, 1>::Apply(values_, v1);
		Detail::ArrayAssign<DimensionCount, 2>::Apply(values_, v2);
	}

	template <std::size_t K>
	const CoordinateType& Get () const {
		static_assert(K < DimensionCount, "K < DimensionCount");
		return values_[K];
	}

	template <std::size_t K>
	void Set (const CoordinateType& value) {
		static_assert(K < DimensionCount, "K < DimensionCount");
		values_[K] = value;
	}

private:
	CoordinateType values_[DimensionCount];
};

namespace Traits {

template <typename CoordinateType, std::size_t DimensionCount>
struct Tag<Point<CoordinateType, DimensionCount>> {
	using Type = PointTag;
};

template <typename CoordinateType, std::size_t DimensionCount, std::size_t Dimension>
struct Access<Point<CoordinateType, DimensionCount>, Dimension> {
	static CoordinateType Get (const Point<CoordinateType, DimensionCount>& point) {
		return point.Get<Dimension>();
	}

	static void Set (Point<CoordinateType, DimensionCount>& point, const CoordinateType& value) {
		point.Set<Dimension>(value);
	}
};

template <typename CoordinateType_, std::size_t DimensionCount>
struct CoordinateType<Point<CoordinateType_, DimensionCount>> {
	using Type = CoordinateType_;
};

template <typename CoordinateType, std::size_t DimensionCount>
struct Dimension<Point<CoordinateType, DimensionCount>>
	: public std::integral_constant<std::size_t, DimensionCount> {
};

} // namespace Traits
} // namespace Index
} // namespace Geometry