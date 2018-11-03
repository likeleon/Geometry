#pragma once

#include "Geometry/Public/Access.h"
#include "Geometry/Public/PointType.h"
#include "Geometry/Public/Tag.h"
#include "Geometry/Public/Tags.h"

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

namespace Traits {

template <typename Point>
struct Tag<Box<Point>> {
	using Type = BoxTag;
};

template <typename Point>
struct PointType<Box<Point>> {
	using Type = Point;
};

template <typename Point, std::size_t Dimension>
struct IndexedAccess<Box<Point>, 0, Dimension> {
	using CoordinateType = typename CoordinateType<Point>::Type;

	static CoordinateType Get (const Box<Point>& box) {
		return Index::Get<Dimension>(box.min_corner());
	}

	static void Set (Box<Point>& box, const CoordinateType& value) {
		Index::Set<Dimension>(box.min_corner(), value);
	}
};

template <typename Point, std::size_t Dimension>
struct IndexedAccess<Box<Point>, 1, Dimension> {
	using CoordinateType = typename CoordinateType<Point>::Type;

	static CoordinateType Get (const Box<Point>& box) {
		return Index::Get<Dimension>(box.max_corner());
	}

	static void Set (Box<Point>& box, const CoordinateType& value) {
		Index::Set<Dimension>(box.max_corner(), value);
	}
};

} // namespace Traits

} // namespace Index
} // namespace Geometry