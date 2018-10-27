#pragma once

namespace Geometry {
namespace Index {

template <typename Point>
class Box {
public:
	Box () = default;

	Box (const Point& min_corner, const Point& max_corner)
		: min_corner_(min_corner), max_corner_(max_corner) {
	}

	const Point& min_corner () const {
		return min_corner_;
	}
	
	Point& min_corner () {
		return min_corner_;
	}

	const Point& max_corner () const {
		return max_corner_;
	}

	Point& max_corner () {
		return max_corner_;
	}

private:
	Point min_corner_;
	Point max_corner_;
};

} // namespace Index
} // namespace Geometry