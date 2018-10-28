#pragma once

#include "Geometry/Public/Point.h"

namespace Geometry {
namespace Index {

template <typename Geometry1, typename Geometry2>
void CheckEqualDimensions () {
	static_assert(Traits::Dimension<Geometry1>::value == Traits::Dimension<Geometry2>::value);
}

} // namespace Index
} // namespace Geometry