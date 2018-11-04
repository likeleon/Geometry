#pragma once

#include "Geometry/Public/Box.h"
#include "Math/Vec3.h"

namespace Geometry {
namespace Index {
namespace Detail {

template <typename Geometry, typename BoundingGeometry>
class BoundedView {
};

// Box -> Box
template <>
class BoundedView<Box, Box> {
public:
	explicit BoundedView (const Box& box)
		: box_(&box) {
	}

	const Math::Vec3& min_corner () const {
		return box_->min_corner();
	}

	const Math::Vec3& max_corner () const {
		return box_->max_corner();
	}

private:
	const Box* box_ = nullptr;
};

// Point -> Box
template <>
class BoundedView<Math::Vec3, Box> {
public:
	explicit BoundedView (const Math::Vec3& point)
		: point_(&point) {
	}

	const Math::Vec3& min_corner () const {
		return *point_;
	}

	const Math::Vec3& max_corner () const {
		return *point_;
	}

private:
	const Math::Vec3* point_ = nullptr;
};

} // namespace Detail
} // namespace Index
} // namespace Geometry