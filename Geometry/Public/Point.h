#pragma once

#include <cstddef>

#include "Geometry/Public/Traits.h"

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
		static_assert(K < DimensionCount);
		return values[K];
	}

	template <std::size_t K>
	void Set (const CoordinateType& value) {
		static_assert(K < DimensionCount);
		values[K] = value;
	}

private:
	CoordinateType values_[DimensionCount];
};

namespace Traits {

template <typename CoordinateType, std::size_t DimensionCount>
struct Cooridnate<Point<CoordinateType, DimensionCount>> {
	using Type = CoordinateType;
};

template <typename CoordinateType, std::size_t DimensionCount>
struct Dimension<Point<CoordinateType, DimensionCount>>
	: std::integral_constant<std::size_t, DimensionCount> {
};

} // namespace Traits
} // namespace Index
} // namespace Geometry