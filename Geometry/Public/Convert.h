#pragma once

#include <cstddef>

#include "Math/Vec3.h"
#include "Geometry/Public/Box.h"

namespace Geometry {
namespace Index {

namespace Detail {

template <typename Geometry1, typename Geometry2>
struct Convert {
};

// 동일한 타입일 경우 operator= 호출
template <typename Geometry1>
struct Convert<Geometry1, Geometry1> {
	static void Apply (const Geometry1& source, Geometry1& destination) {
		destination = source;
	}
};

// Point -> Box
template <>
struct Convert<Math::Vec3, Box> {
	static void Apply (const Math::Vec3& point, Box& box) {
		box.min_corner() = point;
		box.max_corner() = point;
	}
};

} // namespace Detail

template <typename Geometry1, typename Geometry2>
void Convert (const Geometry1& geometry1, Geometry2& geometry2) {
	Detail::Convert<Geometry1, Geometry2>::Apply(geometry1, geometry2);
}

} // namespace Index
} // namespace Geometry