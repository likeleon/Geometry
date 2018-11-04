#pragma once

#include "Geometry/Public/Box.h"
#include "Geometry/Public/BoundedView.h"

namespace Geometry {
namespace Index {
namespace Detail {

template <typename Indexable>
long double Content (const Indexable& indexable) {
	const auto& max = indexable.max_corner();
	const auto& min = indexable.min_corner();
	return (max.x - min.x) * (max.y - min.y) * (max.z - min.z);
}

template <>
long double Content<Math::Vec3> (const Math::Vec3& /*point*/) {
	return 0.0L;
}

} // namespace Detail
} // namespace Index
} // namespace Geometry