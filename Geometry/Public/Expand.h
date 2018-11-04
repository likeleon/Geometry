#pragma once

#include "Geometry/Public/Box.h"
#include "Math/Vec3.h"

namespace Geometry {
namespace Index {

void Expand (Box& box, const Math::Vec3& point) {
	if (point.x < box.min_corner().x) {
		box.min_corner().x = point.x;
	}
	if (point.y < box.min_corner().y) {
		box.min_corner().y = point.y;
	}

	if (point.x > box.max_corner().x) {
		box.max_corner().x = point.x;
	}
	if (point.y > box.max_corner().y) {
		box.max_corner().y = point.y;
	}
};

} // namespace Index
} // namespace Geometry