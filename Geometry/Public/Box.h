#pragma once

#include "Math/Vec3.h"

namespace Geometry {
namespace Index {

class Box {
public:
	Box () = default;

	Box (const Math::Vec3& min_corner, const Math::Vec3& max_corner)
		: min_corner_(min_corner), max_corner_(max_corner) {
	}

	const Math::Vec3& min_corner () const {
		return min_corner_;
	}
	
	Math::Vec3& min_corner () {
		return min_corner_;
	}

	const Math::Vec3& max_corner () const {
		return max_corner_;
	}

	Math::Vec3& max_corner () {
		return max_corner_;
	}

private:
	Math::Vec3 min_corner_;
	Math::Vec3 max_corner_;
};

} // namespace Index
} // namespace Geometry